#include <Windows.h>
#include <Pyx\PyxContext.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void Pyx_OnLoad(Pyx::PyxContext* pPyxContext)
{
    MessageBoxA(nullptr, "Plugin loaded !", "Pyx sample plugin", MB_ICONERROR);
}

extern "C" __declspec(dllexport) void Pyx_OnUnLoad(Pyx::PyxContext* pPyxContext)
{

}