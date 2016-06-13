#pragma once
#include <Pyx/Scripting/Script.h>

namespace LuaModules
{
    namespace Pyx_Win32
    {

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule(XorStringA("Pyx"))
                .beginModule(XorStringA("Win32"))
                .addFunction(XorStringA("GetTickCount"), [pScript]() { return GetTickCount(); })
                .addFunction(XorStringA("TerminateProcess"), [pScript]() { return TerminateProcess(GetCurrentProcess(), 0); });

        }

    }
}
