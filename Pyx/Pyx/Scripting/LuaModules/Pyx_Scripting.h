#pragma once
#include <Pyx/Scripting/Script.h>

namespace LuaModules
{
    namespace Pyx_Scripting
    {

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("Scripting")
                .beginClass<Pyx::Scripting::Script>("Script")
                .addPropertyReadOnly("IsRunning", &Pyx::Scripting::Script::IsRunning)
                .addPropertyReadOnly("Name", &Pyx::Scripting::Script::GetName)
                .addPropertyReadOnly("Directory", &Pyx::Scripting::Script::GetScriptDirectory)
                .addFunction("Start", &Pyx::Scripting::Script::Start)
                .addFunction("Stop", &Pyx::Scripting::Script::Stop)
                .addFunction("RegisterCallback", &Pyx::Scripting::Script::RegisterCallback)
                .addFunction("UnregisterCallback", &Pyx::Scripting::Script::UnregisterCallback)
                .endClass();


            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("Scripting")
                .addProperty("CurrentScript", [pScript]() -> Pyx::Scripting::Script* { return pScript; });

        }

    }
}
