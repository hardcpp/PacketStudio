#pragma once
#include <Pyx/Pyx.h>

namespace Pyx
{
    namespace Graphics
    {
        class GraphicsContext;
        namespace Renderer
        {
            class IRenderer
            {

            public:
                explicit IRenderer() { }
                const char* GetRendererTypeString() const
                {
                    switch (GetRendererType())
                    {
                    case RendererType::D3D9:
                        return "Direct3D9";
                    case RendererType::D3D10:
                        return "Direct3D10";
                    case RendererType::D3D11:
                        return "Direct3D11";
                    case RendererType::OpenGL:
                        return "OpenGL";
                    default:
                        return "Unknown";
                    }
                }
                virtual ~IRenderer() { }
                virtual RendererType GetRendererType() const = 0;
                virtual bool IsActive() const = 0;
                virtual bool IsResourcesCreated() const = 0;
                virtual void CreateResources() = 0;
                virtual void ReleaseResources() = 0;
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