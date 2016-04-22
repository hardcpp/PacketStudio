#include "Context.h"

Pyx::Context* Pyx::Context::s_pMainContext = nullptr;

DWORD WINAPI Pyx::Context::WaitUnloadingThread(LPVOID pData)
{
    Context* pContext = static_cast<Context*>(pData);
    HMODULE hModule = pContext->GetModule();
    PYX_ASSERT_A(pContext->m_unloadCompletedMutex && hModule);
    DWORD result = WaitForSingleObject(pContext->m_unloadCompletedMutex, INFINITE);
    PYX_ASSERT_A(result == WAIT_OBJECT_0);
    CloseHandle(pContext->m_unloadCompletedMutex);
    Sleep(1000); // Make sure we are not in our code anymore, might check R/EIP for faster cleaning ? :p
    delete pContext;
    MessageBoxA(nullptr, XorString("Pyx is unloaded !"), XorString("Pyx"), MB_ICONINFORMATION);
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD Pyx::Context::Initialize(LPVOID pData)
{
    s_pMainContext = new Context(static_cast<HMODULE>(pData));
    s_pMainContext->Unload();
    return 0;
}

Pyx::Context::Context(HMODULE module)
    : m_module(module),
    m_unloadRequested(false),
    m_unloadCompletedMutex(nullptr)
{

    PYX_ASSERT_A(s_pMainContext == nullptr);

    PYX_ASSERT_A(1 == 2);
    MessageBoxA(nullptr, XorString("Pyx is loaded !"), XorString("Pyx"), MB_ICONINFORMATION);

}

void Pyx::Context::RequestUnload()
{
    if (!m_unloadCompletedMutex)
    {
        m_unloadCompletedMutex = CreateMutex(nullptr, true, nullptr);
        PYX_ASSERT_A(m_unloadCompletedMutex != nullptr);
        HANDLE hThread = CreateThread(nullptr, 0, WaitUnloadingThread, this, NULL, nullptr);
        PYX_ASSERT_A(hThread != nullptr);
    }
}

void Pyx::Context::Unload()
{

    if (!IsUnloadedRequested())
    {
        RequestUnload();
    }

    PYX_ASSERT_A(m_unloadCompletedMutex != nullptr);

    // Actually unload from a safe place

    ReleaseMutex(m_unloadCompletedMutex);

}
