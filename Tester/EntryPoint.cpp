#include <Windows.h>
#include <Shlwapi.h>
#include <Pyx/Pyx.h>
#include <Pyx/PyxContext.h>
#include <Pyx/Patch/PatchContext.h>
#include <Pyx/Patch/Detour.h>

#pragma comment(lib,"Shlwapi.lib")

typedef int (WINAPI *tMessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT);
Pyx::Patch::Detour<tMessageBoxW>* g_pMessageBoxWDetour = nullptr;

int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
    return g_pMessageBoxWDetour->GetTrampoline()(hWnd, L"Hooked!", lpCaption, uType);
}

DWORD WINAPI EntryPoint(LPVOID lpParam)
{

    wchar_t moduleFileName[MAX_PATH];
    PYX_ASSERT_A(SUCCEEDED(GetModuleFileNameW(static_cast<HMODULE>(lpParam), moduleFileName, MAX_PATH)))
    PYX_ASSERT_A(PathRemoveFileSpecW(moduleFileName) == TRUE)

    Pyx::PyxInitSettings settings;
    settings.OverlayBlockInput = false;
    settings.RootDirectory = moduleFileName;

    if (!Pyx::PyxContext::CreateContext(settings))
        return -1;

    auto* pPyxContext = Pyx::PyxContext::GetContext();
    pPyxContext->GetPatchContext()->CreateAndApplyDetour<tMessageBoxW>(&MessageBoxW, DetourMessageBoxW, &g_pMessageBoxWDetour);

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