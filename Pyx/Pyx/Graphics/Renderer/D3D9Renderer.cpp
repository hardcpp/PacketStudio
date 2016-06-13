#include <Pyx/Graphics/Renderer/D3D9Renderer.h>
#include <Pyx/Patch/Detour.h>
#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/Graphics/Gui/IGui.h>
#include <Pyx/Utility/String.h>
#include <Pyx/Patch/PatchContext.h>

typedef HRESULT(WINAPI *tIDirect3DDevice9__Present)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
typedef HRESULT(WINAPI *tIDirect3DDevice9__Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

Pyx::Patch::Detour<tIDirect3DDevice9__Present>* g_pIDirect3DDevice9__PresentDetour;
Pyx::Patch::Detour<tIDirect3DDevice9__Reset>* g_pIDirect3DDevice9__ResetDetour;

HRESULT WINAPI IDirect3DDevice9__ResetDetour(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentParameters)
{
    Pyx::Graphics::Renderer::D3D9Renderer::GetInstance().OnResetDevice(pDevice, pPresentParameters);
    auto result = g_pIDirect3DDevice9__ResetDetour->GetTrampoline()(pDevice, pPresentParameters);
    g_pIDirect3DDevice9__ResetDetour->EnsureApply();
    return result;
}

HRESULT WINAPI IDirect3DDevice9__PresentDetour(IDirect3DDevice9* pDevice,
    const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    if (Pyx::PyxContext::GetInstance().IsShutdownedRequested())
    {
        auto result = g_pIDirect3DDevice9__PresentDetour->GetTrampoline()(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        Pyx::PyxContext::GetInstance().Shutdown();
        return result;
    }
    Pyx::Graphics::Renderer::D3D9Renderer::GetInstance().OnPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    auto result = g_pIDirect3DDevice9__PresentDetour->GetTrampoline()(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
    g_pIDirect3DDevice9__PresentDetour->EnsureApply();
    return result;
}

Pyx::Graphics::Renderer::D3D9Renderer::D3D9Renderer()
    : m_isResourceCreated(false), m_pDevice(nullptr), m_pStateBlockOriginal(nullptr), m_pStateBlockCustom(nullptr)
{

}

Pyx::Graphics::Renderer::D3D9Renderer::~D3D9Renderer()
{

}

void Pyx::Graphics::Renderer::D3D9Renderer::Initialize()
{
    if (ApplyHooks())
    {
        
    }
}

void Pyx::Graphics::Renderer::D3D9Renderer::Shutdown()
{
    ReleaseResources();
    if (g_pIDirect3DDevice9__ResetDetour) g_pIDirect3DDevice9__ResetDetour->Remove();
    if (g_pIDirect3DDevice9__PresentDetour) g_pIDirect3DDevice9__PresentDetour->Remove();
}

void Pyx::Graphics::Renderer::D3D9Renderer::CreateResources()
{
    if (m_pDevice)
    {

		if (m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlockOriginal) != D3D_OK)
			return;

		if (m_pDevice->CreateStateBlock(D3DSBT_ALL, &m_pStateBlockCustom) != D3D_OK)
			return;

        m_isResourceCreated = true;
    }
}

void Pyx::Graphics::Renderer::D3D9Renderer::ReleaseResources()
{

	if (m_pStateBlockOriginal)
	{
		m_pStateBlockOriginal->Release();
		m_pStateBlockOriginal = nullptr;
	}

	if (m_pStateBlockCustom)
	{
		m_pStateBlockCustom->Release();
		m_pStateBlockCustom = nullptr;
	}

    auto* pGui = GuiContext::GetInstance().GetGui();
    if (pGui && pGui->IsInitialized())
        pGui->ReleaseResources();

    m_isResourceCreated = false;

}

HWND Pyx::Graphics::Renderer::D3D9Renderer::GetAttachedWindow()
{
    if (m_pDevice)
    {
        D3DDEVICE_CREATION_PARAMETERS parameters;
        if (SUCCEEDED(m_pDevice->GetCreationParameters(&parameters)))
            return parameters.hFocusWindow;
    }
    return nullptr;
}

void Pyx::Graphics::Renderer::D3D9Renderer::SetDevice(IDirect3DDevice9* pDevice)
{
    if (pDevice != m_pDevice)
    {

        PyxContext::GetInstance().Log("[D3D9Renderer] Device 0x%X", pDevice);

        ReleaseResources();
        m_pDevice = pDevice;
        CreateResources();

        auto& graphicsContext = GraphicsContext::GetInstance();

        if (graphicsContext.GetMainRenderer() == nullptr) 
            graphicsContext.SetMainRenderer(this);

        auto* pGui = GuiContext::GetInstance().GetGui();
        if (pGui) pGui->Initialize();

        GetOnIDirect3DDevice9ChangedCallbacks().Run(this, pDevice);

    }
}

void Pyx::Graphics::Renderer::D3D9Renderer::OnResetDevice(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    ReleaseResources();
    SetDevice(pDevice);

    GetOnIDirect3DDevice9__ResetCallbacks().Run(this, pDevice, pPresentationParameters);
}

void Pyx::Graphics::Renderer::D3D9Renderer::OnPresent(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{

    SetDevice(pDevice);

    if (!m_isResourceCreated)
        CreateResources();

    if (m_isResourceCreated)
    {

        m_pStateBlockOriginal->Capture();

        pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
        pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
        pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, 0);
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        pDevice->SetRenderState(D3DRS_LASTPIXEL, TRUE);
        pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
        pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);

        pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
        pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
        pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
        pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_PASSTHRU);
        pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
        pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, 0);
        pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
        pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        pDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);
        pDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
        pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 1);
        pDevice->SetSamplerState(0, D3DSAMP_SRGBTEXTURE, 0);
        pDevice->SetSamplerState(0, D3DSAMP_ELEMENTINDEX, 0);
        pDevice->SetSamplerState(0, D3DSAMP_DMAPOFFSET, 0);

		m_pStateBlockCustom->Capture();

        GetOnIDirect3DDevice9__PresentCallbacks().Run(this, pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

		m_pStateBlockCustom->Apply();
		
        auto* pGui = GuiContext::GetInstance().GetGui();

        if (pGui && pGui->IsInitialized())
            pGui->OnFrame();

        m_pStateBlockOriginal->Apply();

    }

}

bool Pyx::Graphics::Renderer::D3D9Renderer::ApplyHooks()
{

    auto className = Utility::String::GetRandomString(20);

    WNDCLASSEXA wcex;
    memset(&wcex, 0, sizeof wcex);
    wcex.cbSize = sizeof wcex;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.hInstance = nullptr;
    wcex.lpszClassName = className.c_str();
    RegisterClassExA(&wcex);

    auto hWnd = CreateWindowA(className.c_str(), NULL,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL, NULL, nullptr, NULL);

    if (hWnd == nullptr)
        return false;

    auto pIDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);

    if (pIDirect3D9 == nullptr)
    {
        DestroyWindow(hWnd);
        return false;
    }

    D3DPRESENT_PARAMETERS pp{};
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.BackBufferFormat = D3DFMT_UNKNOWN;

    IDirect3DDevice9 *pDevice;
    if (FAILED(pIDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &pDevice)))
    {
        pIDirect3D9->Release();
        DestroyWindow(hWnd);
        return false;
    }

    void** ppVtable = *reinterpret_cast<void***>(pDevice);
    auto& patchContext = Pyx::Patch::PatchContext::GetInstance();

    patchContext.CreateAndApplyDetour<tIDirect3DDevice9__Reset>(
        static_cast<tIDirect3DDevice9__Reset>(ppVtable[16]),
        reinterpret_cast<tIDirect3DDevice9__Reset>(IDirect3DDevice9__ResetDetour),
        &g_pIDirect3DDevice9__ResetDetour);

    patchContext.CreateAndApplyDetour<tIDirect3DDevice9__Present>(
        static_cast<tIDirect3DDevice9__Present>(ppVtable[17]),
        reinterpret_cast<tIDirect3DDevice9__Present>(IDirect3DDevice9__PresentDetour),
        &g_pIDirect3DDevice9__PresentDetour);

    pDevice->Release();
    pIDirect3D9->Release();
    DestroyWindow(hWnd);
    return true;

}

Pyx::Graphics::Renderer::D3D9Renderer& Pyx::Graphics::Renderer::D3D9Renderer::GetInstance()
{
    static D3D9Renderer instance;
    return instance;
}
