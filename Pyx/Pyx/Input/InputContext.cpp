#include <Pyx/Input/InputContext.h>
#include <Windows.h>
#include <Pyx/Patch/Detour.h>
#include <Pyx/Patch/PatchContext.h>
#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/Graphics/Gui/IGui.h>

typedef BOOL(WINAPI *tGetMessageA)(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax);
typedef BOOL(WINAPI *tGetMessageW)(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax);
typedef BOOL(WINAPI *tPeekMessageA)(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);
typedef BOOL(WINAPI *tPeekMessageW)(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg);
typedef BOOL(WINAPI *tGetCursorPos)(LPPOINT lpPoint);
typedef int(WINAPI *tShowCursor)(BOOL bShow);

Pyx::Patch::Detour<tGetMessageA>* g_pGetMessageADetour;
Pyx::Patch::Detour<tGetMessageW>* g_pGetMessageWDetour;
Pyx::Patch::Detour<tPeekMessageA>* g_pPeekMessageADetour;
Pyx::Patch::Detour<tPeekMessageW>* g_pPeekMessageWDetour;
Pyx::Patch::Detour<tShowCursor>* g_pShowCursorDetour;
Pyx::Patch::Detour<tGetCursorPos>* g_pGetCursorPosDetour;

BOOL WINAPI GetMessageADetour(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax)
{
    auto result = g_pGetMessageADetour->GetTrampoline()(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	MSG msg = *lpMsg;
	TranslateMessage(&msg);
    if (result == TRUE && Pyx::Input::InputContext::GetInstance().OnWindowMessage(&msg))
        RtlZeroMemory(lpMsg, sizeof(MSG));
    return result;
}

BOOL WINAPI GetMessageWDetour(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax)
{
    auto result = g_pGetMessageWDetour->GetTrampoline()(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
	MSG msg = *lpMsg;
	TranslateMessage(&msg);
    if (result == TRUE && Pyx::Input::InputContext::GetInstance().OnWindowMessage(&msg))
        RtlZeroMemory(lpMsg, sizeof(MSG));
    return result;
}

BOOL WINAPI PeekMessageADetour(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg)
{
    auto result = g_pPeekMessageADetour->GetTrampoline()(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	MSG msg = *lpMsg;
	TranslateMessage(&msg);
    if (result == TRUE && Pyx::Input::InputContext::GetInstance().OnWindowMessage(&msg))
        RtlZeroMemory(lpMsg, sizeof(MSG));
    return result;
}

BOOL WINAPI PeekMessageWDetour(LPMSG lpMsg, HWND  hWnd, UINT  wMsgFilterMin, UINT  wMsgFilterMax, UINT  wRemoveMsg)
{
    auto result = g_pPeekMessageWDetour->GetTrampoline()(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	MSG msg = *lpMsg;
	TranslateMessage(&msg);
    if (result == TRUE && Pyx::Input::InputContext::GetInstance().OnWindowMessage(&msg))
        RtlZeroMemory(lpMsg, sizeof(MSG));
    return result;
}

BOOL WINAPI GetCursorPosDetour(LPPOINT lpPoint)
{
    auto result = g_pGetCursorPosDetour->GetTrampoline()(lpPoint);
    Pyx::Input::InputContext::GetInstance().OnGetCursorPos(lpPoint);
    return result;
}

int WINAPI ShowCursorDetour(BOOL bShow)
{
    auto result = g_pShowCursorDetour->GetTrampoline()(bShow);
    Pyx::Input::InputContext::GetInstance().OnShowCursor(bShow, &result);
    return result;
}

void Pyx::Input::InputContext::Initialize()
{

    auto& patchContext = Pyx::Patch::PatchContext::GetInstance();

    patchContext.CreateAndApplyDetour<tGetMessageA>(
        static_cast<tGetMessageA>(&GetMessageA),
        reinterpret_cast<tGetMessageA>(GetMessageADetour),
        &g_pGetMessageADetour);

    patchContext.CreateAndApplyDetour<tGetMessageW>(
        static_cast<tGetMessageW>(&GetMessageW),
        reinterpret_cast<tGetMessageW>(GetMessageWDetour),
        &g_pGetMessageWDetour);

    patchContext.CreateAndApplyDetour<tPeekMessageA>(
        static_cast<tPeekMessageA>(&PeekMessageA),
        reinterpret_cast<tPeekMessageA>(PeekMessageADetour),
        &g_pPeekMessageADetour);

    patchContext.CreateAndApplyDetour<tPeekMessageW>(
        static_cast<tPeekMessageW>(&PeekMessageW),
        reinterpret_cast<tPeekMessageW>(PeekMessageWDetour),
        &g_pPeekMessageWDetour);

    patchContext.CreateAndApplyDetour<tShowCursor>(
        static_cast<tShowCursor>(&ShowCursor),
        reinterpret_cast<tShowCursor>(ShowCursorDetour),
        &g_pShowCursorDetour);

    patchContext.CreateAndApplyDetour<tGetCursorPos>(
        static_cast<tGetCursorPos>(&GetCursorPos),
        reinterpret_cast<tGetCursorPos>(GetCursorPosDetour),
        &g_pGetCursorPosDetour);

}

void Pyx::Input::InputContext::Shutdown()
{
    if (g_pGetMessageADetour) g_pGetMessageADetour->Remove();
    if (g_pGetMessageWDetour) g_pGetMessageWDetour->Remove();
    if (g_pPeekMessageADetour) g_pPeekMessageADetour->Remove();
    if (g_pPeekMessageWDetour) g_pPeekMessageWDetour->Remove();
    if (g_pShowCursorDetour) g_pShowCursorDetour->Remove();
    if (g_pGetCursorPosDetour) g_pGetCursorPosDetour->Remove();
}

bool Pyx::Input::InputContext::OnWindowMessage(LPMSG lpMsg)
{
    auto* pGui = Graphics::GuiContext::GetInstance().GetGui();
    if (pGui && pGui->IsInitialized() && pGui->OnWindowMessage(lpMsg))
        return true;

    bool handled = false;

    return handled;
}

bool Pyx::Input::InputContext::OnShowCursor(BOOL bShow, int* pReturnValue)
{
    m_showCursorCount = *pReturnValue;
    return false;
}

bool Pyx::Input::InputContext::OnGetCursorPos(LPPOINT lpPoint)
{
    auto* pGui = Graphics::GuiContext::GetInstance().GetGui();
    if (pGui && pGui->IsInitialized() && pGui->OnGetCursorPos(lpPoint))
        return true;

    return false;
}

POINT Pyx::Input::InputContext::GetCursorPosition()
{
    POINT pt;

    if (g_pGetCursorPosDetour && g_pGetCursorPosDetour->IsApplied())
        g_pGetCursorPosDetour->GetTrampoline()(&pt);
    else
        ::GetCursorPos(&pt);

    return pt;
}

Pyx::Input::InputContext& Pyx::Input::InputContext::GetInstance()
{
    static InputContext ctx;
    return ctx;
}
