#pragma once
#include "../../Pyx.h"
#include "../GraphicsContext.h"
#include "IGui.h"

namespace Pyx
{
    namespace Graphics
    {
        class GuiContext;
        namespace Gui
        {
            class ImGuiImpl : public IGui
            {

            private:
                bool m_isResourcesCreated;
                bool m_isInitialized;

            public:
                explicit ImGuiImpl(GuiContext* pGuiContext);

                ~ImGuiImpl() override { }
                bool IsResourcesCreated() const override { return m_isResourcesCreated; };
                bool IsInitialized() const override { return m_isInitialized; };
                void Initialize() override;
                void Shutdown() override;
                void ReleaseResources() override;
                void CreateResources() override;
                void OnFrame() override;

            };
        }
    }
}
