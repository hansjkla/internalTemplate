#include "hooks.h"

void hooks::Setup()
{
	if (!MinHook)
	{
		if (MH_Initialize())
			throw std::runtime_error("Unable to init minhook.");
	}

	if (MH_CreateHook(
		VirtualFunction(gui::device, 42),
		&EndScene,
		reinterpret_cast<void**>(&EndSceneOriginal)
	)) throw std::runtime_error("Unable to create hook EndScene.");

	if (MH_CreateHook(
		VirtualFunction(gui::device, 16),
		&Reset,
		reinterpret_cast<void**>(&ResetOriginal)
	)) throw std::runtime_error("Unable to create hook Reset.");

	if (MH_EnableHook(VirtualFunction(gui::device, 42)) != MH_OK)
		throw std::runtime_error("Unable to enable hook EndScene.");

	if (MH_EnableHook(VirtualFunction(gui::device, 16)) != MH_OK)
		throw std::runtime_error("Unable to enable hook Reset.");

	MinHook = true;

	//gui::DestroyDirectX();
}


long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept 
{
	static const auto returnAddress = _ReturnAddress();

	const auto result = EndSceneOriginal(device, device);

	if (_ReturnAddress() == returnAddress || uninjecting)
		return result;

	if (!gameWindow)
	{
		auto params = D3DDEVICE_CREATION_PARAMETERS{};
		device->GetCreationParameters(&params);

		gameWindow = params.hFocusWindow;
	}
	
	if (!menu::isMenuSetup)
		menu::SetupMenu(device);

	if (menu::menuOpen)
		menu::Render();

	//D3DRECT rect = { 100, 100, 100 + 100,100 + 50 };
	//device->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 0, 0);

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}
