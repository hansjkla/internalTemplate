#pragma once
#include <d3d9.h>

namespace gui
{
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};

	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline LPDIRECT3D9 d3d9 = nullptr;

	bool SetupWindowClass(const char* windowClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const char* windowName) noexcept;
	void DestroyWindow() noexcept;

	bool SetupDirectX() noexcept;
	bool DestroyDirectX() noexcept;

	bool Setup();
}
