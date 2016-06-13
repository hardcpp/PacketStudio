#pragma once
#include <Pyx/Scripting/Script.h>
#include <Pyx/Graphics/GraphicsContext.h>
#include <Pyx/Graphics/Renderer/IRenderer.h>

namespace LuaModules
{
    namespace Pyx_Input
    {

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("Input")
                .addFunction("IsKeyDown", [pScript](int vKey) { return GetKeyState(vKey) & 0x8000 ? true : false; })
                .addFunction("IsGameForeground", [pScript]() { return Pyx::Graphics::GraphicsContext::GetInstance().GetMainRenderer() && GetForegroundWindow() == Pyx::Graphics::GraphicsContext::GetInstance().GetMainRenderer()->GetAttachedWindow(); });

        }

    }
}
