#pragma once
#include "../../Pyx.h"
#include "../GraphicsContext.h"

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
                GuiContext* m_pGuiContext;

            public:
                explicit IGui(GuiContext* pGuiContext) : m_pGuiContext(pGuiContext) { }
                virtual ~IGui() { }
                GuiContext* GetGuiContext() const { return m_pGuiContext; }
                virtual bool IsResourcesCreated() const = 0;
                virtual void ReleaseResources() = 0;
                virtual void CreateResources() = 0;
                virtual bool IsInitialized() const = 0;
                virtual void Initialize() = 0;
                virtual void Shutdown() = 0;
                virtual void OnFrame() = 0;

            };
        }
    }
}
