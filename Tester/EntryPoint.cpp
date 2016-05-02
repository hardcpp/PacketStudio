#include <Windows.h>
#include <Shlwapi.h>
#include <Pyx/Pyx.h>
#include <Pyx/PyxContext.h>
#include <Pyx/Patch/PatchContext.h>
#include <Pyx/Patch/Detour.h>
#include <Pyx/Graphics/GraphicsContext.h>
#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/Graphics/Gui/IGui.h>
#include <Pyx/Graphics/Renderer/D3D9Renderer.h>
#pragma comment(lib,"Shlwapi.lib")

HMODULE g_hModule = nullptr;

void OnShutdownStarting()
{
    
}

void OnShutdownCompleted()
{
    
    Sleep(1000);
    FreeLibraryAndExitThread(g_hModule, 0);
}

DWORD WINAPI EntryPoint(LPVOID lpParam)
{

    g_hModule = static_cast<HMODULE>(lpParam);

    wchar_t moduleFileName[MAX_PATH];
    GetModuleFileNameW(g_hModule, moduleFileName, MAX_PATH);
    PathRemoveFileSpecW(moduleFileName);

    Pyx::PyxInitSettings settings;
    settings.GuiBlockInput = false;
    settings.RootDirectory = moduleFileName;
    Pyx::PyxContext::GetInstance().Initialize(settings);

    Pyx::PyxContext::GetInstance().GetOnPyxShutdownStartingCallbacks().Register(OnShutdownStarting);
    Pyx::PyxContext::GetInstance().GetOnPyxShutdownCompletedCallbacks().Register(OnShutdownCompleted);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, EntryPoint, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}