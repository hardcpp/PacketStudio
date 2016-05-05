#pragma once
#include <Pyx/Pyx.h>
#include <Pyx/PyxInitSettings.h>
#include <Pyx/Utility/Callbacks.h>
#include <memory>
#include <iostream>
#include <fstream>

namespace Pyx
{
    class PyxContext
    {

    public:
        typedef void tOnPyxShutdownCompletedCallback();
        typedef void tOnPyxShutdownStartingCallback();

    private:
        static DWORD WINAPI WaitShutdowningThread(LPVOID pData);

    public:
        static PyxContext& GetInstance();

    private:
        PyxInitSettings m_settings;
        bool m_ShutdownRequested;
        HANDLE m_hShutdownCompletedEvent;
        std::wofstream m_logFileStream;
        Utility::Callbacks<tOnPyxShutdownStartingCallback> m_OnPyxShutdownStartingCallbacks;
        Utility::Callbacks<tOnPyxShutdownCompletedCallback> m_OnPyxShutdownCompletedCallbacks;

    private:
        explicit PyxContext();
        ~PyxContext();

    public:
        void Initialize(const PyxInitSettings& settings);
        void RequestShutdown();
        void Shutdown();
        bool IsShutdownedRequested() const { return m_ShutdownRequested; }
        const PyxInitSettings& GetSettings() const { return m_settings; }
        void Log(const std::wstring& line);
        void Log(const std::string& line);
        template<typename ... Args>
        void Log(const std::string& format, Args ... args)
        {
            size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
            std::unique_ptr<char[]> buf(new char[size]);
            snprintf(buf.get(), size, format.c_str(), args ...);
            auto str = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
            Log(str);
        }
        template<typename ... Args>
        void Log(const std::wstring& format, Args ... args)
        {
            size_t size = _snwprintf(nullptr, 0, format.c_str(), args ...) + 2;
            std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
            _snwprintf(buf.get(), size, format.c_str(), args ...);
            auto str = std::wstring(buf.get(), buf.get() + size - 2); // We don't want the '\0' inside
            Log(str);
        }
        Utility::Callbacks<tOnPyxShutdownStartingCallback>& GetOnPyxShutdownStartingCallbacks() { return m_OnPyxShutdownStartingCallbacks; }
        Utility::Callbacks<tOnPyxShutdownCompletedCallback>& GetOnPyxShutdownCompletedCallbacks() { return m_OnPyxShutdownCompletedCallbacks; }

    };
}