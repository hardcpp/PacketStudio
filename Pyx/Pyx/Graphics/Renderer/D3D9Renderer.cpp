#include "D3D9Renderer.h"
#include "../GraphicsContext.h"
#include "../../Patch/PatchContext.h"
#include "../../Patch/Detour.h"
#include "../../Utility/String.h"

typedef HRESULT(__stdcall *tIDirect3DDevice9__Present)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);

Pyx::Patch::Detour<tIDirect3DDevice9__Present>* g_pIDirect3DDevice9__PresentDetour;

HRESULT IDirect3DDevice9__PresentDetour(IDirect3DDevice9* pDevice, 
    const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    auto* pPyxContext = Pyx::PyxContext::GetContext();
    if (pPyxContext)
    {

        if (pPyxContext->IsUnloadedRequested())
        {
            pPyxContext->Unload();
            return g_pIDirect3DDevice9__PresentDetour->GetTrampoline()(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        }

        auto* pD3D9Renderer = pPyxContext->GetGraphicsContext()->GetD3D9Renderer();

        if (pD3D9Renderer)
        {
            pD3D9Renderer->SetDevice(pDevice);
            pD3D9Renderer->GetOnIDirect3DDevice9__PresentCallbacks().Run(
                pD3D9Renderer, pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
        }

    }
    return g_pIDirect3DDevice9__PresentDetour->GetTrampoline()(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

Pyx::Graphics::Renderer::D3D9Renderer::D3D9Renderer(GraphicsContext* pGraphicsContext)
    : IRenderer(pGraphicsContext), m_isReleased(false), m_pDevice(nullptr)
{

    void** pVtable;
    if (GetDeviceVTable(&pVtable))
    {

        auto pPatchContext = pGraphicsContext->GetPyxContext()->GetPatchContext();

        pPatchContext->CreateAndApplyDetour<tIDirect3DDevice9__Present>(
            static_cast<tIDirect3DDevice9__Present>(pVtable[17]), 
            reinterpret_cast<tIDirect3DDevice9__Present>(IDirect3DDevice9__PresentDetour),
            &g_pIDirect3DDevice9__PresentDetour);
        
    }

}

Pyx::Graphics::Renderer::D3D9Renderer::~D3D9Renderer()
{
    auto pPatchContext = GetGraphicsContext()->GetPyxContext()->GetPatchContext();
    pPatchContext->RemoveDetour(g_pIDirect3DDevice9__PresentDetour);
}

void Pyx::Graphics::Renderer::D3D9Renderer::Release()
{

    m_isReleased = true;

}

void Pyx::Graphics::Renderer::D3D9Renderer::SetDevice(IDirect3DDevice9* pDevice)
{
    if (pDevice != m_pDevice)
    {
        m_pDevice = pDevice;
        GetOnIDirect3DDevice9ChangedCallbacks().Run(this, pDevice);
    }
}

bool Pyx::Graphics::Renderer::D3D9Renderer::GetDeviceVTable(void*** pppVtable)
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

    *pppVtable = *reinterpret_cast<void***>(pDevice);

    pDevice->Release();
    pIDirect3D9->Release();
    DestroyWindow(hWnd);
    return true;

}
