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

            };
        }
    }
}