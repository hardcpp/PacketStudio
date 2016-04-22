#include "PyxContext.h"

Pyx::PyxContext* Pyx::PyxContext::s_pMainPyxContext = nullptr;

DWORD WINAPI Pyx::PyxContext::WaitUnloadingThread(LPVOID pData)
{
    PyxContext* pPyxContext = static_cast<PyxContext*>(pData);
    HMODULE hModule = pPyxContext->GetModule();
    PYX_ASSERT_A(pPyxContext->m_unloadCompletedMutex && hModule);
    DWORD result = WaitForSingleObject(pPyxContext->m_unloadCompletedMutex, INFINITE);
    PYX_ASSERT_A(result == WAIT_OBJECT_0);
    CloseHandle(pPyxContext->m_unloadCompletedMutex);
    Sleep(1000); // Make sure we are not in our code anymore, might check R/EIP for faster cleaning ? :p
    delete pPyxContext;
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD Pyx::PyxContext::Initialize(LPVOID pData)
{
    s_pMainPyxContext = new PyxContext(static_cast<HMODULE>(pData));
    s_pMainPyxContext->Unload();
    return 0;
}

Pyx::PyxContext::PyxContext(HMODULE module)
    : m_module(module),
    m_unloadRequested(false),
    m_unloadCompletedMutex(nullptr)
{

    PYX_ASSERT_A(s_pMainPyxContext == nullptr);

    m_pSettings = new Settings(this);
    m_pFileSystemContext = new FileSystem::FileSystemContext(this);

    std::wstring settingsXmlFilename = m_pFileSystemContext->GetRootDirectory() + XorStringW(L"\\Settings.xml");
    if (!m_pSettings->LoadFromXml(settingsXmlFilename))
    {
        m_pSettings->SaveToXml(settingsXmlFilename);
    }
    
    MessageBoxW(nullptr, m_pFileSystemContext->GetRootDirectory().c_str(), XorStringW(L"Pyx"), MB_ICONINFORMATION);

}

Pyx::PyxContext::~PyxContext()
{

    if (m_pFileSystemContext)
    {
        delete m_pFileSystemContext;
        m_pFileSystemContext = nullptr;
    }

    if (m_pSettings)
    {
        delete m_pSettings;
        m_pSettings = nullptr;
    }

    MessageBoxA(nullptr, XorStringA("Pyx is unloaded !"), XorStringA("Pyx"), MB_ICONINFORMATION);

}

void Pyx::PyxContext::RequestUnload()
{
    if (!m_unloadCompletedMutex)
    {
        m_unloadCompletedMutex = CreateMutex(nullptr, true, nullptr);
        PYX_ASSERT_A(m_unloadCompletedMutex != nullptr);
        HANDLE hThread = CreateThread(nullptr, 0, WaitUnloadingThread, this, NULL, nullptr);
        PYX_ASSERT_A(hThread != nullptr);
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

    ReleaseMutex(m_unloadCompletedMutex);

}
