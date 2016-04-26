#pragma once
#include "../../Pyx.h"

namespace Pyx
{
    namespace Graphics
    {
        class GraphicsContext;
        namespace Renderer
        {
            class IRenderer
            {

            private:
                GraphicsContext* m_pGraphicsContext;

            public:
                explicit IRenderer(GraphicsContext* pGraphicsContext) : m_pGraphicsContext(pGraphicsContext) { }
                virtual ~IRenderer() { }
                GraphicsContext* GetGraphicsContext() const { return m_pGraphicsContext; }
                virtual RendererType GetRendererType() const = 0;
                virtual bool IsReleased() const = 0;
                virtual void Release() = 0;
                virtual HWND GetAttachedWindow() = 0;
                virtual bool GetResolution(int& x, int& y)
                {
                    RECT rect;
                    if (GetClientRect(GetAttachedWindow(), &rect) == TRUE)
                    {
                        x = rect.right - rect.left;
                        y = rect.bottom - rect.top;
                        return true;
                    }
                    return false;
                }

            };
        }
    }
}