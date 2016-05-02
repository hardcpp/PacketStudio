#pragma once
#include <Windows.h>
#include "../PyxContext.h"

namespace Pyx
{
    namespace Threading
    {
        class Thread
        {

        private:
            HANDLE m_hThread;
            DWORD m_threadId;
            bool m_isSuspended;

        public:
            explicit Thread(DWORD threadId)
                : m_isSuspended(false)
            {
                m_hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadId);
                m_threadId = threadId;
            }
            ~Thread() { CloseHandle(m_hThread); }
            DWORD GetThreadId() const { return m_threadId; }
            HANDLE GetThreadHandle() const { return m_hThread; }
            bool SuspendThread()
            {
                m_isSuspended = ::SuspendThread(m_hThread) != (DWORD)-1;
                return m_isSuspended;
            }
            bool ResumeThread()
            {
                m_isSuspended = ::ResumeThread(m_hThread) == (DWORD)-1;
                return !m_isSuspended;
            }

        };
    }
}
