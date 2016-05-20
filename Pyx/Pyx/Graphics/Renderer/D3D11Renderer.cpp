#include <Pyx/Graphics/Renderer/D3D11Renderer.h>
#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/PyxContext.h>
#include <Pyx/Patch/PatchContext.h>
#include <Pyx/Graphics/GraphicsContext.h>
#include <Pyx/Graphics/Gui/IGui.h>
#include <Pyx/Patch/Detour.h>

typedef void(WINAPI *tID3D11DeviceContext__OMSetRenderTargets)(ID3D11DeviceContext* pContext, unsigned int numViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView);

Pyx::Patch::Detour<tID3D11DeviceContext__OMSetRenderTargets>* g_pID3D11DeviceContext__OMSetRenderTargets;

void WINAPI ID3D11DeviceContext__OMSetRenderTargetsDetour(ID3D11DeviceContext* pContext, unsigned int numViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
    Pyx::Graphics::Renderer::D3D11Renderer::GetInstance().OnOMSetRenderTargets(pContext, numViews, ppRenderTargetViews, pDepthStencilView);
    g_pID3D11DeviceContext__OMSetRenderTargets->GetTrampoline()(pContext, numViews, ppRenderTargetViews, pDepthStencilView);
    g_pID3D11DeviceContext__OMSetRenderTargets->EnsureApply();
}

void Pyx::Graphics::Renderer::D3D11Renderer::ApplyDevicesHook()
{
}

Pyx::Graphics::Renderer::D3D11Renderer& Pyx::Graphics::Renderer::D3D11Renderer::GetInstance()
{
    static D3D11Renderer instance;
    return instance;
}

Pyx::Graphics::Renderer::D3D11Renderer::D3D11Renderer()
    : m_isResourceCreated(false), 
    m_pSwapChain(nullptr), 
    m_pDevice(nullptr), 
    m_pDeviceContext(nullptr), 
    m_pStateBlockOriginal(nullptr), 
    m_pStateBlockCustom(nullptr), 
    m_pDefaultBlendState(nullptr)
{
}

Pyx::Graphics::Renderer::D3D11Renderer::~D3D11Renderer()
{
}

void Pyx::Graphics::Renderer::D3D11Renderer::Initialize()
{
}

void Pyx::Graphics::Renderer::D3D11Renderer::Shutdown()
{
    ReleaseResources();
}

void Pyx::Graphics::Renderer::D3D11Renderer::CreateResources()
{

    if (m_pDevice)
        m_pDevice->GetImmediateContext(&m_pDeviceContext);

	if (m_pDevice == nullptr || m_pDeviceContext == nullptr)
		return;

    m_pStateBlockOriginal = new D3D11StateBlock(m_pDeviceContext);
    m_pStateBlockCustom = new D3D11StateBlock(m_pDeviceContext);

    D3D11_BLEND_DESC blend = {};
    blend.RenderTarget[0].BlendEnable = TRUE;
    blend.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    blend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    m_pDevice->CreateBlendState(&blend, &m_pDefaultBlendState);

    m_isResourceCreated = true;
}

void Pyx::Graphics::Renderer::D3D11Renderer::ReleaseResources()
{

    if (m_pDeviceContext)
    {
        m_pDeviceContext->Release();
        m_pDeviceContext = nullptr;
    }

    if (m_pDefaultBlendState)
    {
        m_pDefaultBlendState->Release();
        m_pDefaultBlendState = nullptr;
    }

	if (m_pStateBlockOriginal)
	{
		delete m_pStateBlockOriginal;
		m_pStateBlockOriginal = nullptr;
	}

	if (m_pStateBlockCustom)
	{
		delete m_pStateBlockCustom;
		m_pStateBlockCustom = nullptr;
	}

    auto* pGui = GuiContext::GetInstance().GetGui();
    if (pGui && pGui->IsInitialized())
        pGui->ReleaseResources();

    m_isResourceCreated = false;
}

HWND Pyx::Graphics::Renderer::D3D11Renderer::GetAttachedWindow()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    if (m_pSwapChain && m_pSwapChain->GetDesc(&swapChainDesc) == S_OK)
        return swapChainDesc.OutputWindow;
    return nullptr;
}

void Pyx::Graphics::Renderer::D3D11Renderer::SetDevice(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain)
{
    if (pDevice != m_pDevice || pSwapChain != m_pSwapChain)
    {

        PyxContext::GetInstance().Log("[D3D11Renderer] Device 0x%X, SwapChain 0x%X", pDevice, pSwapChain);

        ApplyDevicesHook();

        ReleaseResources();
        m_pDevice = pDevice;
        m_pSwapChain = pSwapChain;
        CreateResources();

        auto& graphicsContext = GraphicsContext::GetInstance();

        if (graphicsContext.GetMainRenderer() == nullptr)
            graphicsContext.SetMainRenderer(this);

        auto* pGui = GuiContext::GetInstance().GetGui();
        if (pGui) pGui->Initialize();

		ID3D11DeviceContext* pDeviceContext;
		pDevice->GetImmediateContext(&pDeviceContext);

		if (pDeviceContext)
		{

			GetOnDeviceChangedCallbacks().Run(this, pSwapChain, pDevice);

			void** ppDeviceContextVtable = *reinterpret_cast<void***>(pDeviceContext);

			if (!g_pID3D11DeviceContext__OMSetRenderTargets)
			{
				auto& patchContext = Pyx::Patch::PatchContext::GetInstance();
				patchContext.CreateAndApplyDetour<tID3D11DeviceContext__OMSetRenderTargets>(
					static_cast<tID3D11DeviceContext__OMSetRenderTargets>(ppDeviceContextVtable[33]),
					reinterpret_cast<tID3D11DeviceContext__OMSetRenderTargets>(ID3D11DeviceContext__OMSetRenderTargetsDetour),
					&g_pID3D11DeviceContext__OMSetRenderTargets);
			}
		
			pDeviceContext->Release();
		}

    }
}

void Pyx::Graphics::Renderer::D3D11Renderer::OnResizeBuffers(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
    ReleaseResources();
    SetDevice(pDevice, pSwapChain);
    GetOnResizeBuffersCallbacks().Run(this, pSwapChain, pDevice, bufferCount, width, height, newFormat, swapChainFlags);
}

void Pyx::Graphics::Renderer::D3D11Renderer::OnResizeTarget(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, DXGI_MODE_DESC* pNewTargetParameters)
{
    ReleaseResources();
    SetDevice(pDevice, pSwapChain);
    GetOnResizeTargetCallbacks().Run(this, pSwapChain, pDevice, pNewTargetParameters);
}

void Pyx::Graphics::Renderer::D3D11Renderer::OnOMSetRenderTargets(ID3D11DeviceContext* pContext, unsigned numViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
    GetOnOMSetRenderTargetsCallbacks().Run(this, pContext, numViews, ppRenderTargetViews, pDepthStencilView);
}

void Pyx::Graphics::Renderer::D3D11Renderer::OnPresent(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    SetDevice(pDevice, pSwapChain);

    if (!m_isResourceCreated)
        CreateResources();
    
    m_pStateBlockOriginal->Capture();

    m_pDeviceContext->CSSetShader(nullptr, nullptr, 0);
    m_pDeviceContext->DSSetShader(nullptr, nullptr, 0);
    m_pDeviceContext->GSSetShader(nullptr, nullptr, 0);
    m_pDeviceContext->HSSetShader(nullptr, nullptr, 0);
    m_pDeviceContext->OMSetBlendState(m_pDefaultBlendState, nullptr, 0xFFFFFFFF);

    ID3D11Texture2D* pBackBuffer = nullptr;
    if (pSwapChain->GetBuffer(0, __uuidof(*pBackBuffer), reinterpret_cast<void**>(&pBackBuffer)) == S_OK)
    {
        D3D11_TEXTURE2D_DESC bb_surf_desc = {};
        pBackBuffer->GetDesc(&bb_surf_desc);

        D3D11_VIEWPORT viewport = {};
        viewport.Width = static_cast<float>(bb_surf_desc.Width);
        viewport.Height = static_cast<float>(bb_surf_desc.Height);
        viewport.MaxDepth = 1;
        m_pDeviceContext->RSSetViewports(1, &viewport);

        ID3D11RenderTargetView* pRtv = nullptr;
        if (pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRtv) == S_OK)
        {
            m_pDeviceContext->OMSetRenderTargets(1, &pRtv, nullptr);
            pRtv->Release();
        }

        pBackBuffer->Release();
    }

	m_pStateBlockCustom->Capture();
    
    GetOnPresentCallbacks().Run(this, pSwapChain, pDevice);

	m_pStateBlockCustom->Apply();

    auto* pGui = GuiContext::GetInstance().GetGui();

    if (pGui && pGui->IsInitialized())
        pGui->OnFrame();
    
    m_pStateBlockOriginal->Apply();

}
