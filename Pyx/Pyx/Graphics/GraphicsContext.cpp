#include "GraphicsContext.h"
#include "../Pyx.h"
#include "Renderer/D3D9Renderer.h"

Pyx::Graphics::GraphicsContext::GraphicsContext(PyxContext* pPyxContext)
    : m_pPyxContext(pPyxContext), m_pMainRenderer(nullptr)
{
    m_pD3D9Renderer = new Renderer::D3D9Renderer(this);
}

Pyx::Graphics::GraphicsContext::~GraphicsContext()
{

    if (m_pD3D9Renderer != nullptr)
    {
        delete m_pD3D9Renderer;
        m_pD3D9Renderer = nullptr;
    }

}

void Pyx::Graphics::GraphicsContext::SetMainRenderer(Renderer::IRenderer* pRenderer)
{
    PYX_ASSERT_A(pRenderer != nullptr);
    m_pMainRenderer = pRenderer;
}
