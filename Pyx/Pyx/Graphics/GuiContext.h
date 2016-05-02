#pragma once
#include <d3d9.h>

namespace Pyx
{
    namespace Graphics
    {
        namespace Gui
        {
            class IGui;
        }
        class GraphicsContext;
        class GuiContext
        {
        public:
            static GuiContext& GetInstance();

        private:
            Gui::IGui* m_pGui;

        public:
            explicit GuiContext();
            ~GuiContext();
            void Shutdown();
            Gui::IGui* GetGui();
        };
    }
}
