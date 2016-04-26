#include "ImGuiImpl.h"
#include "../GuiContext.h"
#include "../GraphicsContext.h"
#include "../Renderer/IRenderer.h"
#include "../Renderer/D3D9Renderer.h"
#include "../../../ImGui/imgui.h"
#include "../../../ImGui/imgui_impl_dx9.h"

Pyx::Graphics::Gui::ImGuiImpl::ImGuiImpl(GuiContext* pGuiContext)
    : IGui(pGuiContext), m_isResourcesCreated(false), m_isInitialized(false)
{
    
}

void Pyx::Graphics::Gui::ImGuiImpl::Initialize()
{

    if (m_isInitialized)
        Shutdown();

    auto* pGraphicsContext = GetGuiContext()->GetGraphicsContext();
    auto* pRenderer = pGraphicsContext->GetMainRenderer();
    if (pRenderer)
    {
        switch (pRenderer->GetRendererType())
        {
        case RendererType::D3D9:
        {            
            auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
            auto* pDevice9 = pD3D9Renderer->GetDevice();
            if (pDevice9)
            {
                ImGui_ImplDX9_Init(pD3D9Renderer->GetAttachedWindow(), pDevice9);
                if (!m_isResourcesCreated) CreateResources();
                m_isInitialized = true;
            }
            break;
        }
        default:
            return;
        }
    }
    
}

void Pyx::Graphics::Gui::ImGuiImpl::Shutdown()
{
    if (m_isInitialized)
    {

        if (m_isResourcesCreated)
            ReleaseResources();

        auto* pGraphicsContext = GetGuiContext()->GetGraphicsContext();
        auto* pRenderer = pGraphicsContext->GetMainRenderer();
        if (pRenderer)
        {
            switch (pRenderer->GetRendererType())
            {
            case RendererType::D3D9:
            {
                auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
                auto* pDevice9 = pD3D9Renderer->GetDevice();
                if (pDevice9)
                {
                    ImGui_ImplDX9_InvalidateDeviceObjects();
                    m_isInitialized = false;
                }
                break;
            }
            default:
                return;
            }
        }
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::ReleaseResources()
{
    if (m_isResourcesCreated)
    {
        auto* pGraphicsContext = GetGuiContext()->GetGraphicsContext();
        auto* pRenderer = pGraphicsContext->GetMainRenderer();
        switch (pRenderer->GetRendererType())
        {
        case RendererType::D3D9:
        {
            auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
            auto* pDevice9 = pD3D9Renderer->GetDevice();
            if (pDevice9)
            {
                ImGui_ImplDX9_InvalidateDeviceObjects();
                m_isResourcesCreated = false;
            }
            break;
        }
        default:
            return;
        }
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::CreateResources()
{
    if (!m_isResourcesCreated)
    {
        auto* pGraphicsContext = GetGuiContext()->GetGraphicsContext();
        auto* pRenderer = pGraphicsContext->GetMainRenderer();
        switch (pRenderer->GetRendererType())
        {
        case RendererType::D3D9:
        {
            auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
            auto* pDevice9 = pD3D9Renderer->GetDevice();
            if (pDevice9)
            {
                m_isResourcesCreated = ImGui_ImplDX9_CreateDeviceObjects();
            }
            break;
        }
        default:
            return;
        }
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::OnFrame()
{
    if (m_isInitialized)
    {

        if (!m_isResourcesCreated)
            CreateResources();

        if (m_isResourcesCreated)
        {

            auto* pGraphicsContext = GetGuiContext()->GetGraphicsContext();
            auto* pRenderer = pGraphicsContext->GetMainRenderer();
            switch (pRenderer->GetRendererType())
            {
            case RendererType::D3D9:
            {
                auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
                auto* pDevice9 = pD3D9Renderer->GetDevice();
                if (pDevice9)
                {
                    ImGui_ImplDX9_NewFrame();
                }
                break;
            }
            default:
                return;
            }

            ImGui::Render();

        }

    }
}
