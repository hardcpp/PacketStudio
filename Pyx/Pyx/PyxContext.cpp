#include "PyxContext.h"
#include "Pyx.h"
#include "Patch/PatchContext.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer/D3D9Renderer.h"
#include "Graphics/Renderer/DXGI.h"
#include "Graphics/GuiContext.h"
#include "Graphics/Gui/IGui.h"
#include "Threading/ThreadContext.h"
#include "Threading/Thread.h"
#include "Input/InputContext.h"
#include "Graphics/Renderer/D3D11Renderer.h"
#include <iomanip>
#include <ctime>
#include "Scripting/ScriptingContext.h"

Pyx::PyxContext* s_pPyxContext = nullptr;

DWORD Pyx::PyxContext::WaitShutdowningThread(LPVOID pData)
{
    auto& pyxContext = GetInstance();
    auto result = WaitForSingleObject(pyxContext.m_hShutdownCompletedEvent, INFINITE);
    CloseHandle(pyxContext.m_hShutdownCompletedEvent);
    pyxContext.GetOnPyxShutdownCompletedCallbacks().Run();
    return 0;
}

Pyx::PyxContext& Pyx::PyxContext::GetInstance()
{
    static PyxContext ctx;
    return ctx;
}

Pyx::PyxContext::PyxContext()
    : m_ShutdownRequested(false), 
    m_hShutdownCompletedEvent(nullptr)
{
    
}

Pyx::PyxContext::~PyxContext()
{

}

void Pyx::PyxContext::Initialize(const PyxInitSettings& settings)
{

    m_settings = settings;

    if (m_settings.LogToFile)
    {
        std::wstring logsDirectory = m_settings.RootDirectory + m_settings.LogDirectory;
        std::wstring logFileName = logsDirectory + L"\\logs_" + std::to_wstring(GetCurrentProcessId()) + L".log";
        CreateDirectoryW(logsDirectory.c_str(), nullptr);
        m_logFileStream.open(logFileName.c_str(), std::ofstream::out);
    }

    Patch::PatchContext::GetInstance().Initialize();

    auto suspendedThreads = Threading::ThreadContext::GetInstance().SuspendAllThreads();

    Graphics::Renderer::D3D9Renderer::GetInstance().Initialize();
    Graphics::Renderer::DXGI::GetInstance().Initialize();
    Input::InputContext::GetInstance().Initialize();
    Scripting::ScriptingContext::GetInstance().Initialize();

    for (auto thread : suspendedThreads)
        thread->ResumeThread();

}

void Pyx::PyxContext::RequestShutdown()
{
    if (!m_hShutdownCompletedEvent)
    {
        m_hShutdownCompletedEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        HANDLE hThread = CreateThread(nullptr, 0, WaitShutdowningThread, nullptr, NULL, nullptr);
        CloseHandle(hThread);
        m_ShutdownRequested = true;
    }
}

void Pyx::PyxContext::Shutdown()
{

    if (!IsShutdownedRequested())
        RequestShutdown();

    auto suspendedThreads = Threading::ThreadContext::GetInstance().SuspendAllThreads();

    GetOnPyxShutdownStartingCallbacks().Run();
    Scripting::ScriptingContext::GetInstance().Shutdown();
    Graphics::GuiContext::GetInstance().Shutdown();
    Graphics::Renderer::D3D9Renderer::GetInstance().Shutdown();
    Graphics::Renderer::D3D11Renderer::GetInstance().Shutdown();
    Graphics::Renderer::DXGI::GetInstance().Shutdown();
    Input::InputContext::GetInstance().Shutdown();
    Patch::PatchContext::GetInstance().Shutdown();

    for (auto thread : suspendedThreads)
        thread->ResumeThread();

    if (m_logFileStream.is_open())
        m_logFileStream.close();

    SetEvent(m_hShutdownCompletedEvent);

}

void Pyx::PyxContext::Log(const std::wstring& line)
{

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    wchar_t buffer[256];
    wcsftime(buffer, sizeof(buffer), L"[%H:%M:%S] ", &tm);
    std::wstring timedLine = std::wstring(buffer) + line;

    if (GetSettings().LogToFile && m_logFileStream.is_open())
        m_logFileStream << timedLine.c_str() << std::endl;

    auto* pGui = Graphics::GuiContext::GetInstance().GetGui();
    if (pGui) pGui->Logger_OnWriteLine(timedLine);

}

void Pyx::PyxContext::Log(const std::string& line)
{
    Log(std::wstring(line.begin(), line.end()));
}
