#include "PyxContext.h"
#include "Pyx.h"
#include "Patch/PatchContext.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/GuiContext.h"

Pyx::PyxContext* s_pPyxContext = nullptr;

DWORD Pyx::PyxContext::WaitUnloadingThread(LPVOID pData)
{
    PyxContext* pPyxContext = static_cast<PyxContext*>(pData);
    PYX_ASSERT_A(pPyxContext->m_unloadCompletedMutex);
    DWORD result = WaitForSingleObject(pPyxContext->m_unloadCompletedMutex, INFINITE);
    PYX_ASSERT_A(result == WAIT_OBJECT_0);
    CloseHandle(pPyxContext->m_unloadCompletedMutex);
    pPyxContext->GetOnPyxUnloadCompletedCallbacks().Run(pPyxContext);
    return 0;
}

bool Pyx::PyxContext::CreateContext(const PyxInitSettings& settings)
{
    if (s_pPyxContext == nullptr)
    {
        s_pPyxContext = new PyxContext(settings);
        return true;
    }
    return false;
}

void Pyx::PyxContext::DestroyContext()
{
    if (s_pPyxContext != nullptr)
    {
        delete s_pPyxContext;
        s_pPyxContext = nullptr;
    }
}

Pyx::PyxContext* Pyx::PyxContext::GetContext()
{
    return s_pPyxContext;
}

Pyx::PyxContext::PyxContext(const PyxInitSettings& settings)
    : m_settings(settings), 
    m_unloadRequested(false), 
    m_unloadCompletedMutex(nullptr)
{

    // TODO : Suspend threads

    m_pPatchContext = new Patch::PatchContext(this);
    m_pGraphicsContext = new Graphics::GraphicsContext(this);

    // TODO : Resume threads

}

Pyx::PyxContext::~PyxContext()
{

    if (m_pGraphicsContext)
    {
        delete m_pGraphicsContext;
        m_pGraphicsContext = nullptr;
    }

    if (m_pPatchContext)
    {
        delete m_pPatchContext;
        m_pPatchContext = nullptr;
    }

}

void Pyx::PyxContext::RequestUnload()
{
    if (!m_unloadCompletedMutex)
    {
        m_unloadCompletedMutex = CreateMutex(nullptr, true, nullptr);
        PYX_ASSERT_A(m_unloadCompletedMutex != nullptr);
        HANDLE hThread = CreateThread(nullptr, 0, WaitUnloadingThread, this, NULL, nullptr);
        PYX_ASSERT_A(hThread != nullptr);
        CloseHandle(hThread);
    }
}

void Pyx::PyxContext::Unload()
{

    if (!IsUnloadedRequested())
    {
        RequestUnload();
    }

    PYX_ASSERT_A(m_unloadCompletedMutex != nullptr);

    // Actually unload from a safe place
    GetOnPyxUnloadStartingCallbacks().Run(this);

    ReleaseMutex(m_unloadCompletedMutex);

}
