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
        class GraphicsContext
        {
        private:
            PyxContext* m_pPyxContext;
            Renderer::IRenderer* m_pMainRenderer;
            Renderer::D3D9Renderer* m_pD3D9Renderer;

        public:
            explicit GraphicsContext(PyxContext* pPyxContext);
            ~GraphicsContext();
            PyxContext* GetPyxContext() const { return m_pPyxContext; }
            Renderer::IRenderer* GetMainRenderer() const { return m_pMainRenderer; }
            Renderer::D3D9Renderer* GetD3D9Renderer() const { return m_pD3D9Renderer; }
            void SetMainRenderer(Renderer::IRenderer* pRenderer);
        };
    }
}