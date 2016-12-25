#pragma once
#include <Pyx/Scripting/Script.h>

namespace LuaModules
{
    namespace Pyx_Scripting
    {

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {
            LuaBinding(pScript->GetLuaState()).beginModule(XorStringA("Pyx"))
                .beginModule(XorStringA("Scripting"))
                .beginClass<Pyx::Scripting::Script>(XorStringA("Script"))
                .addPropertyReadOnly(XorStringA("IsRunning"), &Pyx::Scripting::Script::IsRunning)
                .addPropertyReadOnly(XorStringA("Name"), &Pyx::Scripting::Script::GetName)
                .addPropertyReadOnly(XorStringA("Directory"), &Pyx::Scripting::Script::GetScriptDirectory)
                .addFunction(XorStringA("Start"), &Pyx::Scripting::Script::Start)
                .addFunction(XorStringA("Stop"), &Pyx::Scripting::Script::Stop)
                .addFunction(XorStringA("RegisterCallback"), &Pyx::Scripting::Script::RegisterCallback)
                .addFunction(XorStringA("UnregisterCallback"), &Pyx::Scripting::Script::UnregisterCallback)
                .endClass();

            LuaBinding(pScript->GetLuaState()).beginModule(XorStringA("Pyx"))
                .beginModule(XorStringA("Scripting"))
                .addProperty(XorStringA("CurrentScript"), [pScript]() -> Pyx::Scripting::Script* { return pScript; });

        }

    }
}
