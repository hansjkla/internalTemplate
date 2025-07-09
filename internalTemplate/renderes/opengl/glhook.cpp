#include "glhook.h"

wglSwapBuffers_t owglSwapBuffers = nullptr;
LPVOID glHook::targetFunc = nullptr;

bool glHook::GlEnabled = false;
GL::Font glHook::glFont;


unsigned int glHook::base = 0;

BOOL __stdcall glHook::hkwglSawpBuffers(HDC hDc)
{
    if (uninjecting) return owglSwapBuffers(hDc);

    HDC currentHDC = wglGetCurrentDC();
    if (!glFont.bBuilt || currentHDC != glFont.hDc)
    {
        glFont.Build(15);
    }

    if (!gameWindow) gameWindow = WindowFromDC(wglGetCurrentDC());

    base = glFont.base;

    GL::SetupOrtho();

    RenderQueue::ExecuteAll();
    menu::SetupMenu(nullptr);
    menu::Render();

    GL::RestoreGl();
    
	return owglSwapBuffers(hDc);
}

bool glHook::CreateGl()
{
    // Save the real address of the function
    targetFunc = (LPVOID)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
    if (!targetFunc)
        return false;

    //owglSwapBuffers = (wglSwapBuffers_t)targetFunc;

    if (!MinHook)
    {
        if (MH_Initialize() != MH_OK)
            return false;
    }

    // Hook the real address, and store original in owglSwapBuffers
    if (MH_CreateHook(targetFunc, &hkwglSawpBuffers, (LPVOID*)&owglSwapBuffers) != MH_OK)
        return false;

    // Enable hook on the actual address
    if (MH_EnableHook(targetFunc) != MH_OK)
        return false;

    MinHook = true;
    GlEnabled = true;
    return true;
}

bool glHook::DisableGl()
{
    if (MH_DisableHook(targetFunc) != MH_OK)
        return false;

    GlEnabled = false;
    return true;
}

bool glHook::EnableGl()
{
    if (MH_EnableHook(targetFunc) != MH_OK)
        return false;

    GlEnabled = true;
    return true;
}

bool glHook::DestroyGl()
{
    if (MH_RemoveHook(targetFunc) != MH_OK)
        return false;

    GlEnabled = false;
    return true;
}

