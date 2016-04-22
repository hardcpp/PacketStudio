#pragma once
#include <Windows.h>
#include <cassert>
#include <mutex>
#include <sstream>

#include "Utility/String.h"
#include "FileSystem/FileSystemContext.h"
#include "Settings.h"

#define PYX_ASSERT_A(cond) if (!(cond)) { std::stringstream ss; ss << XorStringA("Assertion : ") << XorStringA(#cond) << XorStringA("\r\nFile : ") << XorStringA(__FILE__) << XorStringA("\r\nLine : ") << __LINE__; MessageBoxA(nullptr, ss.str().c_str(), XorStringA("Assertion failure"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1); }
#define PYX_ASSERT_W(cond) if (!(cond)) { std::stringstream ss; ss << XorStringW(L"Assertion : ") << XorStringW(#cond) << XorStringA(L"\r\nFile : ") << XorStringW(__FILE__) << XorStringW(L"\r\nLine : ") << __LINE__; MessageBoxW(nullptr, ss.str().c_str(), XorStringW(L"Assertion failure"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1); }
#define PYX_FATAL_ERROR_A(msg) MessageBoxA(nullptr, XorStringA(msg), XorStringA("Fatal error"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1);
#define PYX_FATAL_ERROR_W(msg) MessageBoxA(nullptr, XorStringW(msg), XorStringW("Fatal error"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1);

namespace Pyx
{
    class PyxContext
    {
        
    private:
        static PyxContext* s_pMainPyxContext;

    private:
        static DWORD WINAPI WaitUnloadingThread(LPVOID pData);

    public:
        static DWORD WINAPI Initialize(LPVOID pData);
        static PyxContext* GetPyxContext() { return s_pMainPyxContext; }
        
    private:
        Settings* m_pSettings;
        FileSystem::FileSystemContext* m_pFileSystemContext;
        HMODULE m_module;
        bool m_unloadRequested;
        HANDLE m_unloadCompletedMutex;

    public:
        explicit PyxContext(HMODULE module);
        ~PyxContext();
        virtual HMODULE GetModule() const { return m_module; }
        virtual bool IsUnloadedRequested() const { return m_unloadRequested; }
        virtual HANDLE GetUnloadCompletedMutex() const { return m_unloadCompletedMutex; }
        virtual const Settings* GetSettings() const { return m_pSettings; }
        virtual const FileSystem::FileSystemContext* GetFileSystemContext() const { return m_pFileSystemContext; }
        virtual void RequestUnload();
        void Unload();

    };
}