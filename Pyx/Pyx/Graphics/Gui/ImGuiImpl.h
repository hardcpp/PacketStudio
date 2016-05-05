#pragma once
#include <Pyx/Graphics/GraphicsContext.h>
#include <Pyx/Pyx.h>
#include "IGui.h"
#include <mutex>
#include <vector>

namespace Pyx
{
    namespace Graphics
    {
        class GuiContext;
        namespace Gui
        {
            class ImGuiImpl : public IGui
            {

            public:
                static ImGuiImpl& GetInstance();

            private:
                bool m_isResourcesCreated;
                bool m_isInitialized;
                bool m_showDebugWindow;
                std::vector<std::string> m_logsItems;
                bool m_logScrollToEnd = false;
                POINT m_lastValidMousePosition;

            public:
                explicit ImGuiImpl();
                ~ImGuiImpl() override;
                GuiType GetGuiType() const override { return GuiType::ImGui; }
                bool IsResourcesCreated() const override { return m_isResourcesCreated; };
                bool IsInitialized() const override { return m_isInitialized; };
                void Initialize() override;
                void Shutdown() override;
                void ReleaseResources() override;
                void CreateResources() override;
                void OnFrame() override;
                bool OnWindowMessage(const MSG* lpMsg) override;
                void Logger_OnWriteLine(const std::wstring& line) override;
                bool OnGetCursorPos(LPPOINT lpPoint) override;
                void SetupStyle(bool bDarkStyle) const;
                void BuildMainMenuBar();
                void BuildDebugWindow();
                void BuildLogsWindow();

            };
        }
    }
}
