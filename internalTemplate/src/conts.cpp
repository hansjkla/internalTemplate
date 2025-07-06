#include "conts.h"

bool console = false;
bool MinHook = false;

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t baseAddress = (uintptr_t)GetModuleHandle(nullptr);
