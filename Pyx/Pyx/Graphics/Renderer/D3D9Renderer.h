#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include "IRenderer.h"
#include "../../Utility/Callbacks.h"

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

            public:
                static bool GetDeviceVTable(void*** ppVtable);

            private:
                bool m_isReleased;
                IDirect3DDevice9* m_pDevice;
                Utility::Callbacks<tOnIDirect3DDevice9__PresentCallback> m_OnIDirect3DDevice9__PresentCallbacks;
                Utility::Callbacks<tOnIDirect3DDevice9Changed> m_OnIDirect3DDevice9ChangedCallbacks;

            public:
                explicit D3D9Renderer(GraphicsContext* pGraphicsContext);
                ~D3D9Renderer() override;
                RendererType GetRendererType() const override { return RendererType::D3D9; }
                bool IsReleased() const override { return m_isReleased; }
                void Release() override;
                IDirect3DDevice9* GetDevice() const { return m_pDevice; }
                void SetDevice(IDirect3DDevice9* pDevice);
                Utility::Callbacks<tOnIDirect3DDevice9__PresentCallback>& GetOnIDirect3DDevice9__PresentCallbacks() { return m_OnIDirect3DDevice9__PresentCallbacks; }
                Utility::Callbacks<tOnIDirect3DDevice9Changed>& GetOnIDirect3DDevice9ChangedCallbacks() { return m_OnIDirect3DDevice9ChangedCallbacks; }
            
            };
        }
    }
}
