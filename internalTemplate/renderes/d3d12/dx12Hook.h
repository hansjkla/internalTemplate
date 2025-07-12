#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include "../../ext/mihook/minhook.h"
#include "../../src/conts.h"
#include "../menu/menu.h"

typedef HRESULT(__stdcall* t_Present)(IDXGISwapChain*, UINT, UINT);

namespace Dx12Hook
{
	extern bool Dx12Enabled;

	extern t_Present PtroPresent;
	extern t_Present oPresent;

	extern bool D3DInitalized;

	extern ID3D12Device* device;
	extern ID3D12Resource* backBuffer;
	extern ID3D12DescriptorHeap* descriptorHeap;
	extern ID3D12CommandAllocator* commandAlloc;
	extern D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	extern ID3D12GraphicsCommandList* commandList;

	HRESULT __stdcall hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);

	bool getPtrPresent();

	bool CreateHook();
	bool Activate();
	bool Deactivate();

	void Destroy();
}
