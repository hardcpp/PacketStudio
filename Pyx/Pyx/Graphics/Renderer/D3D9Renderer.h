#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include "IRenderer.h"
#include <Pyx/Utility/Callbacks.h>

namespace Pyx
{
    namespace Graphics
    {
        namespace Renderer
        {
            class D3D9Renderer : public IRenderer
            {

            public:
                typedef void tOnIDirect3DDevice9Changed(D3D9Renderer* pRenderer, IDirect3DDevice9* pDevice);
                typedef void tOnIDirect3DDevice9__PresentCallback(D3D9Renderer* pRenderer, IDirect3DDevice9* pDevice,
                    const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
                typedef void tOnIDirect3DDevice9__ResetCallback(D3D9Renderer* pRenderer, IDirect3DDevice9* pDevice,
                    D3DPRESENT_PARAMETERS* pPresentationParameters);

            private:
                static bool ApplyHooks();

            public:
                static D3D9Renderer& GetInstance();

            private:
                bool m_isResourceCreated;
                IDirect3DDevice9* m_pDevice; 
                IDirect3DStateBlock9* m_pStateBlock;
                Utility::Callbacks<tOnIDirect3DDevice9__PresentCallback> m_OnIDirect3DDevice9__PresentCallbacks;
                Utility::Callbacks<tOnIDirect3DDevice9__ResetCallback> m_OnIDirect3DDevice9__ResetCallbacks;
                Utility::Callbacks<tOnIDirect3DDevice9Changed> m_OnIDirect3DDevice9ChangedCallbacks;

            public:
                explicit D3D9Renderer();
                ~D3D9Renderer() override;
                void Initialize();
                void Shutdown();
                RendererType GetRendererType() const override { return RendererType::D3D9; }
                bool IsResourcesCreated() const override { return m_isResourceCreated; }
                bool IsActive() const override { return m_pDevice != nullptr; }
                void CreateResources() override;
                void ReleaseResources() override;
                HWND GetAttachedWindow() override;
                IDirect3DDevice9* GetDevice() const { return m_pDevice; }
                void SetDevice(IDirect3DDevice9* pDevice);
                void OnPresent(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
                void OnResetDevice(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
                Utility::Callbacks<tOnIDirect3DDevice9__PresentCallback>& GetOnIDirect3DDevice9__PresentCallbacks() { return m_OnIDirect3DDevice9__PresentCallbacks; }
                Utility::Callbacks<tOnIDirect3DDevice9__ResetCallback>& GetOnIDirect3DDevice9__ResetCallbacks() { return m_OnIDirect3DDevice9__ResetCallbacks; }
                Utility::Callbacks<tOnIDirect3DDevice9Changed>& GetOnIDirect3DDevice9ChangedCallbacks() { return m_OnIDirect3DDevice9ChangedCallbacks; }
            
            };
        }
    }
}
