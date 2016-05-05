#pragma once
#include <Pyx/Pyx.h>
#include <Pyx/Graphics/GraphicsContext.h>

namespace Pyx
{
    namespace Graphics
    {
        class GuiContext;
        namespace Gui
        {
            class IGui
            {

            private:
                DWORD m_pulseThreadId;
                DWORD m_renderThreadId;

            public:
                explicit IGui() { }
                virtual ~IGui() { }
                const char* GetGuiTypeString() const
                {
                    switch (GetGuiType())
                    {
                    case GuiType::ImGui:
                        return "ImGui";
                    default:
                        return "Unknown";
                    }
                }
                virtual GuiType GetGuiType() const = 0;
                virtual bool IsResourcesCreated() const = 0;
                virtual void ReleaseResources() = 0;
                virtual void CreateResources() = 0;
                virtual bool IsInitialized() const = 0;
                virtual void Initialize() = 0;
                virtual void Shutdown() = 0;
                virtual void OnFrame() = 0;
                virtual bool OnWindowMessage(const MSG* lpMsg) { return false; }
                virtual void Logger_OnWriteLine(const std::wstring& line) { }
                virtual bool OnGetCursorPos(LPPOINT lpPoint) { return false; }

            };
        }
    }
}
