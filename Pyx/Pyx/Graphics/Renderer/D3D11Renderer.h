#pragma once
#include <Pyx/Graphics/Renderer/IRenderer.h>
#include <Pyx/Graphics/Renderer/D3D11StateBlock.h>
#include <Pyx/Utility/Callbacks.h>
#include <dxgi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

namespace Pyx
{
    namespace Graphics
    {
        namespace Renderer
        {
            class D3D11Renderer : public IRenderer
            {

            public:
                typedef void tOnDeviceChanged(D3D11Renderer* pRenderer, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice);
                typedef void tOnPresent(D3D11Renderer* pRenderer, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice);
                typedef void tOnResizeBuffers(D3D11Renderer* pRenderer, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
                typedef void tOnResizeTarget(D3D11Renderer* pRenderer, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, DXGI_MODE_DESC *pNewTargetParameters);
                typedef void tOnOMSetRenderTargets(D3D11Renderer* pRenderer, ID3D11DeviceContext* pContext, unsigned int numViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView);

            private:
                static void ApplyDevicesHook();

            public:
                static D3D11Renderer& GetInstance();

            private:
                bool m_isResourceCreated;
                IDXGISwapChain* m_pSwapChain;
                ID3D11Device* m_pDevice;
                ID3D11DeviceContext* m_pDeviceContext;
                D3D11StateBlock* m_pStateBlock;
                ID3D11BlendState* m_pDefaultBlendState;
                Utility::Callbacks<tOnDeviceChanged> m_OnDeviceChangedCallbacks;
                Utility::Callbacks<tOnPresent> m_OnPresentCallbacks;
                Utility::Callbacks<tOnResizeBuffers> m_OnResizeBuffersCallbacks;
                Utility::Callbacks<tOnResizeTarget> m_OnResizeTargetCallbacks;
                Utility::Callbacks<tOnOMSetRenderTargets> m_OnOMSetRenderTargetsCallbacks;

            public:
                explicit D3D11Renderer();
                ~D3D11Renderer() override;
                void Initialize();
                void Shutdown();
                RendererType GetRendererType() const override { return RendererType::D3D11; }
                bool IsResourcesCreated() const override { return m_isResourceCreated; }
                bool IsActive() const override { return m_pDevice != nullptr && m_pSwapChain != nullptr; }
                void CreateResources() override;
                void ReleaseResources() override;
                HWND GetAttachedWindow() override;
                ID3D11Device* GetDevice() const { return m_pDevice; }
                IDXGISwapChain* GetSwapChain() const { return m_pSwapChain; }
                void SetDevice(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain);
                void OnPresent(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
                void OnResizeBuffers(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
                void OnResizeTarget(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, DXGI_MODE_DESC *pNewTargetParameters);
                void OnOMSetRenderTargets(ID3D11DeviceContext* pContext, unsigned int numViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView);
                Utility::Callbacks<tOnDeviceChanged>& GetOnDeviceChangedCallbacks() { return m_OnDeviceChangedCallbacks; }
                Utility::Callbacks<tOnPresent>& GetOnPresentCallbacks() { return m_OnPresentCallbacks; }
                Utility::Callbacks<tOnResizeBuffers>& GetOnResizeBuffersCallbacks() { return m_OnResizeBuffersCallbacks; }
                Utility::Callbacks<tOnResizeTarget>& GetOnResizeTargetCallbacks() { return m_OnResizeTargetCallbacks; }
                Utility::Callbacks<tOnOMSetRenderTargets>& GetOnOMSetRenderTargetsCallbacks() { return m_OnOMSetRenderTargetsCallbacks; }

            };
        }
    }
}
