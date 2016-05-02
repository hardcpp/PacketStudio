#include "DXGI.h"
#include <dxgi.h>
#include "../../PyxContext.h"
#include "../../Patch/Detour.h"
#include "../GraphicsContext.h"
#include "../GuiContext.h"
#include "../../Patch/PatchContext.h"
#include "../../Utility/String.h"
#include <d3d11.h>
#include <d3d10.h>
#include "D3D11Renderer.h"
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3d11.lib")

typedef HRESULT(WINAPI *tIDXGISwapChain__Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(WINAPI *tIDXGISwapChain__ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
typedef HRESULT(WINAPI *tIDXGISwapChain__ResizeTarget)(IDXGISwapChain* pSwapChain, DXGI_MODE_DESC *pNewTargetParameters);

Pyx::Patch::Detour<tIDXGISwapChain__Present>* g_pIDXGISwapChain__PresentDetour;
Pyx::Patch::Detour<tIDXGISwapChain__ResizeBuffers>* g_pIDXGISwapChain__ResizeBuffersDetour;
Pyx::Patch::Detour<tIDXGISwapChain__ResizeTarget>* g_pIDXGISwapChain__ResizeTargetDetour;

HRESULT WINAPI IDXGISwapChain__PresentDetour(struct IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (Pyx::PyxContext::GetInstance().IsShutdownedRequested())
    {
        auto result = g_pIDXGISwapChain__PresentDetour->GetTrampoline()(pSwapChain, SyncInterval, Flags);
        Pyx::PyxContext::GetInstance().Shutdown();
        return result;
    }

    ID3D10Device* pD3D10Device = nullptr;
    ID3D11Device* pD3D11Device = nullptr;

    if (pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pD3D11Device)) == S_OK
        && pD3D11Device
        && pD3D11Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0)
    {
        Pyx::Graphics::Renderer::D3D11Renderer::GetInstance().OnPresent(pD3D11Device, pSwapChain, SyncInterval, Flags);
    }

    if (pD3D11Device) pD3D11Device->Release();

    auto result = g_pIDXGISwapChain__PresentDetour->GetTrampoline()(pSwapChain, SyncInterval, Flags);
    g_pIDXGISwapChain__PresentDetour->EnsureApply();
    return result;
}

HRESULT WINAPI IDXGISwapChain__ResizeBuffersDetour(IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
    ID3D10Device* pD3D10Device = nullptr;
    ID3D11Device* pD3D11Device = nullptr;

    if (pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pD3D11Device)) == S_OK
        && pD3D11Device
        && pD3D11Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0)
    {
        Pyx::Graphics::Renderer::D3D11Renderer::GetInstance().OnResizeBuffers(pD3D11Device, pSwapChain, bufferCount, width, height, newFormat, swapChainFlags);
    }

    if (pD3D11Device) pD3D11Device->Release();

    auto result = g_pIDXGISwapChain__ResizeBuffersDetour->GetTrampoline()(pSwapChain, bufferCount, width, height, newFormat, swapChainFlags);
    g_pIDXGISwapChain__ResizeBuffersDetour->EnsureApply();
    return result;
}

HRESULT WINAPI IDXGISwapChain__ResizeTargetDetour(IDXGISwapChain* pSwapChain, DXGI_MODE_DESC *pNewTargetParameters) 
{
    ID3D10Device* pD3D10Device = nullptr;
    ID3D11Device* pD3D11Device = nullptr;

    if (pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pD3D11Device)) == S_OK
        && pD3D11Device
        && pD3D11Device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0)
    {
        Pyx::Graphics::Renderer::D3D11Renderer::GetInstance().OnResizeTarget(pD3D11Device, pSwapChain, pNewTargetParameters);
    }

    if (pD3D11Device) pD3D11Device->Release();

    auto result = g_pIDXGISwapChain__ResizeTargetDetour->GetTrampoline()(pSwapChain, pNewTargetParameters);
    g_pIDXGISwapChain__ResizeTargetDetour->EnsureApply();
    return result;
}

void Pyx::Graphics::Renderer::DXGI::Initialize()
{
    if (ApplyHooks())
    {
        
    }
}

void Pyx::Graphics::Renderer::DXGI::Shutdown()
{
    if (g_pIDXGISwapChain__PresentDetour) g_pIDXGISwapChain__PresentDetour->Remove();
    if (g_pIDXGISwapChain__ResizeBuffersDetour) g_pIDXGISwapChain__ResizeBuffersDetour->Remove();
    if (g_pIDXGISwapChain__ResizeTargetDetour) g_pIDXGISwapChain__ResizeTargetDetour->Remove();
}

Pyx::Graphics::Renderer::DXGI& Pyx::Graphics::Renderer::DXGI::GetInstance()
{
    static DXGI instance;
    return instance;
}

bool Pyx::Graphics::Renderer::DXGI::ApplyHooks()
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

    IDXGISwapChain* pSwapChain;
    ID3D10Device *pDevice;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    HRESULT result = D3D10CreateDeviceAndSwapChain(nullptr, D3D10_DRIVER_TYPE_HARDWARE, nullptr, NULL, D3D10_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice);

    if (result != S_OK)
    {
        if (pSwapChain) pSwapChain->Release();
        if (pDevice) pDevice->Release();
        DestroyWindow(hWnd);
        return false;
    }

    void** ppVtable = *reinterpret_cast<void***>(pSwapChain);
    auto& patchContext = Pyx::Patch::PatchContext::GetInstance();

    patchContext.CreateAndApplyDetour<tIDXGISwapChain__Present>(
        static_cast<tIDXGISwapChain__Present>(ppVtable[8]),
        reinterpret_cast<tIDXGISwapChain__Present>(IDXGISwapChain__PresentDetour),
        &g_pIDXGISwapChain__PresentDetour);

    patchContext.CreateAndApplyDetour<tIDXGISwapChain__ResizeBuffers>(
        static_cast<tIDXGISwapChain__ResizeBuffers>(ppVtable[13]),
        reinterpret_cast<tIDXGISwapChain__ResizeBuffers>(IDXGISwapChain__ResizeBuffersDetour),
        &g_pIDXGISwapChain__ResizeBuffersDetour);

    patchContext.CreateAndApplyDetour<tIDXGISwapChain__ResizeTarget>(
        static_cast<tIDXGISwapChain__ResizeTarget>(ppVtable[14]),
        reinterpret_cast<tIDXGISwapChain__ResizeTarget>(IDXGISwapChain__ResizeTargetDetour),
        &g_pIDXGISwapChain__ResizeTargetDetour);

    if (pSwapChain) pSwapChain->Release();
    if (pDevice) pDevice->Release();
    DestroyWindow(hWnd);
    return true;

}
