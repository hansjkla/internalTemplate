#include "conts.h"

bool console = false;
bool MinHook = false;
bool uninjecting = false;

extern HWND gameWindow = nullptr;

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t baseAddress = (uintptr_t)GetModuleHandle(nullptr);
