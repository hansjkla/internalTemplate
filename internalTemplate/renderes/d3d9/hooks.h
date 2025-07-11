#pragma once
#include "gui.h"
#include "../../src/conts.h"
#include "../../utils/funcs.h"
//
#include <stdexcept>
#include <intrin.h>

#include "../../ext/mihook/minhook.h"

#include "drawing.h"
//
namespace hooks
{
	extern LPDIRECT3DDEVICE9 realDevice;

	void Setup();
	
	constexpr void* VirtualFunction(void* thisptr, size_t index) noexcept
	{
		return (*static_cast<void***>(thisptr))[index];
	}

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal = nullptr;
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;
	
	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal = nullptr;
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;
}
