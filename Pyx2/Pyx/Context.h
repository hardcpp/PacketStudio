#pragma once
#include <Windows.h>
#include <cassert>
#include <mutex>

#define PYX_ASSERT(...) assert(__VA_ARGS__)

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