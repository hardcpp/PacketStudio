#include <Pyx/Threading/ThreadContext.h>
#include <Pyx/Threading/Thread.h>
#include <tlhelp32.h>

Pyx::Threading::ThreadContext& Pyx::Threading::ThreadContext::GetInstance()
{
    static ThreadContext ctx;
    return ctx;
}

Pyx::Threading::ThreadContext::ThreadContext()
{

}

std::vector<std::shared_ptr<Pyx::Threading::Thread>> Pyx::Threading::ThreadContext::GetThreads() const
{
    std::vector<std::shared_ptr<Thread>> results;
    THREADENTRY32 te32;
    DWORD currentProcessId = GetCurrentProcessId();
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap != NULL)
    {

        // Fill in the size of the structure before using it. 
        te32.dwSize = sizeof(THREADENTRY32);

        // Retrieve information about the first thread,
        // and exit if unsuccessful
        if (Thread32First(hThreadSnap, &te32))
        {
            do
            {
                if (te32.th32OwnerProcessID == currentProcessId)
                {
                    results.push_back(std::make_shared<Thread>(te32.th32ThreadID));
                }
            } 
            while (Thread32Next(hThreadSnap, &te32));
        }

        //  Don't forget to clean up the snapshot object.
        CloseHandle(hThreadSnap);
    }
    return results;
}

std::vector<std::shared_ptr<Pyx::Threading::Thread>> Pyx::Threading::ThreadContext::SuspendAllThreads() const
{
    std::vector<std::shared_ptr<Thread>> results;
    for (auto thread : GetThreads())
    {
        if (thread->GetThreadId() != GetCurrentThreadId() && thread->SuspendThread())
        {
            results.push_back(thread);
        }
    }
    return results;
}

Pyx::Threading::ThreadContext::~ThreadContext()
{

}
