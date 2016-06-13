#pragma once

namespace Pyx
{
    class PyxContext;
    namespace Graphics
    {
        namespace Renderer
        {
            class IRenderer;
            class D3D9Renderer;
        }
        class GuiContext;
        class GraphicsContext
        {

        public:
            static GraphicsContext& GetInstance();

        private:
            Renderer::IRenderer* m_pMainRenderer;

        public:
            explicit GraphicsContext();
            ~GraphicsContext();
            Renderer::IRenderer* GetMainRenderer() const { return m_pMainRenderer; }
            void SetMainRenderer(Renderer::IRenderer* pRenderer);
        };
    }
}