#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <Pyx/Graphics/Renderer/IRenderer.h>
#include <Pyx/Utility/Callbacks.h>

namespace Pyx
{
    namespace Graphics
    {
        namespace Renderer
        {
            class DXGI
            {
                
            public:
                static DXGI& GetInstance();

            private:
                static bool ApplyHooks();

            public:
                void Initialize();
                void Shutdown();

            };
        }
    }
}
