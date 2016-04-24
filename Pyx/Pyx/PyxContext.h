#pragma once
#include "Pyx.h"
#include "PyxInitSettings.h"
#include "Utility/Callbacks.h"

namespace Pyx
{
    namespace Patch
    {
        class PatchContext;
    }
    class PyxContext
    {

    public:
        typedef void tOnPyxUnloadCompletedCallback(PyxContext* pPyxContext);
        typedef void tOnPyxUnloadStartingCallback(PyxContext* pPyxContext);

    private:
        static DWORD WINAPI WaitUnloadingThread(LPVOID pData);

    public:
        static bool CreateContext(const PyxInitSettings& settings);
        static void DestroyContext();
        static PyxContext* GetContext();

    private:
        PyxInitSettings m_settings;
        Patch::PatchContext* m_pPatchContext;
        bool m_unloadRequested;
        HANDLE m_unloadCompletedMutex;
        Utility::Callbacks<tOnPyxUnloadStartingCallback> m_OnPyxUnloadStartingCallbacks;
        Utility::Callbacks<tOnPyxUnloadCompletedCallback> m_OnPyxUnloadCompletedCallbacks;

    private:
        explicit PyxContext(const PyxInitSettings& settings);
        ~PyxContext();

    public:
        bool IsUnloadedRequested() const { return m_unloadRequested; }
        const PyxInitSettings& GetSettings() const { return m_settings; }
        Patch::PatchContext* GetPatchContext() const { return m_pPatchContext; }
        void RequestUnload();
        void Unload();
        Utility::Callbacks<tOnPyxUnloadStartingCallback>& GetOnPyxUnloadStartingCallbacks() { return m_OnPyxUnloadStartingCallbacks; }
        Utility::Callbacks<tOnPyxUnloadCompletedCallback>& GetOnPyxUnloadCompletedCallbacks() { return m_OnPyxUnloadCompletedCallbacks; }

    };
}