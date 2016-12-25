#include <Pyx/Graphics/GraphicsContext.h>
#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/Graphics/Gui/IGui.h>
#include <Pyx/Graphics/Renderer/IRenderer.h>
#include <Pyx/PyxContext.h>

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
    PyxContext::GetInstance().Log(XorStringA("[Graphics] Using renderer : ") + std::string(pRenderer->GetRendererTypeString()));
	auto pGui = GuiContext::GetInstance().GetGui();
	if (pGui) pGui->ToggleVisibility(true);
}
