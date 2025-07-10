#include "dx11Hook.h"

bool Dx11Hook::Dx11Enabled = false;

t_Present Dx11Hook::PtroPresent = nullptr;
t_Present Dx11Hook::oPresent = nullptr;

bool Dx11Hook::D3DInitalized = false;

ID3D11Device* Dx11Hook::device = nullptr;
ID3D11DeviceContext* Dx11Hook::devcon = nullptr;
ID3D11RenderTargetView* Dx11Hook::renderTargetView = nullptr;

HRESULT __stdcall Dx11Hook::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	if (uninjecting) return oPresent(swapChain, syncInterval, flags);

	if (!D3DInitalized)
	{
		swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device);
		device->GetImmediateContext(&devcon);

		ID3D11Texture2D* pBackBuffer = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
		device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView);
		pBackBuffer->Release();

		menu::SetupMenu();

		D3DInitalized = true;
	}

	devcon->OMSetRenderTargets(1, &renderTargetView, nullptr);

	menu::Render();

	return oPresent(swapChain, syncInterval, flags);
}


bool Dx11Hook::getPtrPresent()
{
	HWND Window = GetForegroundWindow();
	gameWindow = Window;

	DXGI_SWAP_CHAIN_DESC scd{ 0 };

	scd.BufferCount = 2;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = Window;
	scd.SampleDesc.Count = 1;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain *swapChain;
	ID3D11Device *device;

	D3D_FEATURE_LEVEL featureLvl[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		featureLvl,
		2,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		nullptr,
		nullptr
	) == S_OK)
	{
		void** PvTable = *reinterpret_cast<void***>(swapChain);

		swapChain->Release();
		device->Release();

		oPresent = (t_Present)(PvTable[8]);
		PtroPresent = oPresent;

		return true;
	}
	return false;
}


bool Dx11Hook::CreateHook()
{
	if (!getPtrPresent())
		return false;

	if (!MinHook)
	{
		if (MH_Initialize() != MH_OK)
			return false;
		MinHook = true;
	}

	if (MH_CreateHook((LPVOID)PtroPresent, &hkPresent, (LPVOID*)&oPresent) != MH_OK)
		return false;

	if (MH_EnableHook(PtroPresent) != MH_OK)
		return false;

	Dx11Enabled = true;
	return true;
}


bool Dx11Hook::Activate()
{
	if (MH_EnableHook(oPresent) != MH_OK)
		return false;

	Dx11Enabled = true;
	return true;
}


bool Dx11Hook::Deactivate()
{
	if (MH_DisableHook(oPresent) != MH_OK)
		return false;

	Dx11Enabled = false;
	return true;
}


void Dx11Hook::Destroy()
{
	device->Release();
	devcon->Release();
}
