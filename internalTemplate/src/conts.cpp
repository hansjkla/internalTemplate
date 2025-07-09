#include "conts.h"

bool console = false;
bool MinHook = false;
bool uninjecting = false;

HWND gameWindow = nullptr;

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t baseAddress = (uintptr_t)GetModuleHandle(nullptr);
