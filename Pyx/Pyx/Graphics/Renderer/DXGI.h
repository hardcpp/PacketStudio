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
