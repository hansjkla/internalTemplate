#pragma once
#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_win32.h"

#include "../../ext/imgui/imgui_impl_opengl3.h"
#include "../../ext/imgui/imgui_impl_dx9.h"
#include "../../ext/imgui/imgui_impl_dx11.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "../../src/conts.h"
#include "../RendererOptions.h"
#include "../d3d9/gui.h"
#include "../d3d9/hooks.h"
#include "../d3d11/dx11Hook.h"

LRESULT CALLBACK WindowsProcess(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

namespace menu
{
	extern bool isMenuSetup;
	extern bool menuOpen;
	extern bool showDemoWindow;

	inline WNDPROC originalWindowProcess = nullptr;

	void SetupMenu();
	void Render();
	void Destroy();
}
