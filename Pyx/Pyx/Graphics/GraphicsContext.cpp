#include "GraphicsContext.h"
#include "GuiContext.h"
#include "../Pyx.h"
#include "../PyxContext.h"
#include "Renderer/D3D9Renderer.h"

Pyx::Graphics::GraphicsContext& Pyx::Graphics::GraphicsContext::GetInstance()
{
    static GraphicsContext ctx;
    return ctx;
}

Pyx::Graphics::GraphicsContext::GraphicsContext()
    : m_pMainRenderer(nullptr)
{

}

Pyx::Graphics::GraphicsContext::~GraphicsContext()
{

}

void Pyx::Graphics::GraphicsContext::SetMainRenderer(Renderer::IRenderer* pRenderer)
{
    PYX_ASSERT_A(pRenderer != nullptr);
    m_pMainRenderer = pRenderer;
    PyxContext::GetInstance().Log("[Graphics] Using renderer : " + std::string(pRenderer->GetRendererTypeString()));
}
