#pragma once
#include <Windows.h>
#include <iostream>
#include <functional>
#include <vector>
#include <mutex>
#include "../../ext/mihook/minhook.h"
#include "../../src/conts.h"
#include "gltext.h"
#include "gldraw.h"
#include "../picker.h"

typedef BOOL(__stdcall* wglSwapBuffers_t) (HDC hDc);
extern wglSwapBuffers_t owglSwapBuffers;

namespace glHook
{
	extern unsigned int base;

	extern LPVOID targetFunc;
	extern bool GlEnabled;
	BOOL __stdcall hkwglSawpBuffers(HDC hDc);
	bool CreateGl();
	bool DisableGl();
	bool EnableGl();
	bool DestroyGl();
}
