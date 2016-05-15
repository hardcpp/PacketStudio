#pragma once
#include <Pyx/Scripting/Script.h>

namespace LuaModules
{
    namespace Pyx_Win32
    {

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("Win32")
                .addFunction("GetTickCount", [pScript]() { return GetTickCount(); })
                .addFunction("TerminateProcess", [pScript]() { return TerminateProcess(GetCurrentProcess(), 0); });

        }

    }
}
