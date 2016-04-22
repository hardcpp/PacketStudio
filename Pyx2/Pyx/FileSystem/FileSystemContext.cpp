#include <Shlwapi.h>
#include "FileSystemContext.h"
#include "../PyxContext.h"

Pyx::FileSystem::FileSystemContext::FileSystemContext(PyxContext* pPyxContext)
    : m_pPyxContext(pPyxContext)
{

    PYX_ASSERT_A(pPyxContext != nullptr);

    wchar_t moduleFileName[MAX_PATH];
    PYX_ASSERT_A(SUCCEEDED(GetModuleFileNameW(pPyxContext->GetModule(), moduleFileName, MAX_PATH)))
    PYX_ASSERT_A(PathRemoveFileSpecW(moduleFileName) == TRUE)
    m_rootDirectory = moduleFileName;
    
}

bool Pyx::FileSystem::FileSystemContext::FileExists(const std::string& fileName) const
{
    return true;
}

bool Pyx::FileSystem::FileSystemContext::FileExists(const std::wstring& fileName) const
{
    return true;
}
