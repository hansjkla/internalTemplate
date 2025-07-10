#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "../../ext/mihook/minhook.h"
#include "../../src/conts.h"
#include "../menu/menu.h"

typedef HRESULT(__stdcall* t_Present)(IDXGISwapChain*, UINT, UINT);

namespace Dx11Hook
{
	extern bool Dx11Enabled;

	extern t_Present PtroPresent;
	extern t_Present oPresent;

	extern bool D3DInitalized;
	extern ID3D11Device* device;
	extern ID3D11DeviceContext* devcon;
	extern ID3D11RenderTargetView* renderTargetView;

	HRESULT __stdcall hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);

	bool getPtrPresent();

	bool CreateHook();
	bool Activate();
	bool Deactivate();

	void Destroy();
}
