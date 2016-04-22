#pragma once
#include <Windows.h>
#include <cassert>
#include <mutex>
#include <sstream>
#include "Utility/String.h"

#define PYX_ASSERT_A(cond) if (!(cond)) { std::stringstream ss; ss << XorString("Assertion : ") << XorString(#cond) << "\r\nFile : " << XorString(__FILE__) << XorString("\r\nLine : ") << __LINE__; MessageBoxA(nullptr, ss.str().c_str(), XorString("Assertion failure"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1); }

namespace Pyx
{
    class Context
    {
        
    private:
        static Context* s_pMainContext;

    private:
        static DWORD WINAPI WaitUnloadingThread(LPVOID pData);

    public:
        static DWORD WINAPI Initialize(LPVOID pData);
        static Context* GetContext() { return s_pMainContext; }
        
    private:
        HMODULE m_module;
        bool m_unloadRequested;
        HANDLE m_unloadCompletedMutex;

    public:
        Context(HMODULE module);
        HMODULE GetModule() const { return m_module; }
        bool IsUnloadedRequested() const { return m_unloadRequested; }
        HANDLE GetUnloadCompletedMutex() const { return m_unloadCompletedMutex; }
        void RequestUnload();
        void Unload();

    };
}