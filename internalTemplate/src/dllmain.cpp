#include "../utils/includes.h"
#include "main.h"

HANDLE thread = nullptr;

void Setup(HMODULE instance)
{
    entryPoint();
    func::unload(instance);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Setup, hModule, 0, nullptr);
    }

    return TRUE;
}
