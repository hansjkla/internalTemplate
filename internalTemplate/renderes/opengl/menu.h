#pragma once
#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_win32.h"
#include "../../ext/imgui/imgui_impl_opengl3.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/GL.h>

#include "glhook.h"

namespace menuGL
{
	extern bool setupMenuGL;
	extern bool showDemoWindow;
	inline WNDPROC originalWindowProcessx = nullptr;

	bool SetupImGuiGL();
	void renderDemoWindow();
	void Destroy();
}
