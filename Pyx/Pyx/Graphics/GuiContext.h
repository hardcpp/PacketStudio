#pragma once

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
        private:
            GraphicsContext* m_pGraphicsContext;
            Gui::IGui* m_pGui;

        public:
            explicit GuiContext(GraphicsContext* pGraphicsContext);
            ~GuiContext();
            GraphicsContext* GetGraphicsContext() const { return m_pGraphicsContext; }
        };
    }
}