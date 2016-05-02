#pragma once
#include <Pyx/Scripting/Script.h>

namespace LuaModules
{
    namespace Override
    {
        inline void lua_Print(Pyx::Scripting::Script* pScript, lua_State* L)
        {
            int num = lua_gettop(L);
            for (int i = 1; i <= num; i++)
            {
                std::string luaStrValue;
                switch (lua_type(L, i))
                {
                case LUA_TSTRING:
                {
                    const char* pStr = lua_tolstring(L, i, nullptr);
                    luaStrValue = pStr ? pStr : "";
                    break;
                }
                case LUA_TBOOLEAN:
                {
                    luaStrValue = lua_toboolean(L, i) ? "true" : "false";
                    break;
                }
                case LUA_TNUMBER:
                {
                    luaStrValue = std::to_string(lua_tonumber(L, i));
                    break;
                }
                default:
                    lua_getglobal(L, "tostring");
                    if (lua_isfunction(L, -1))
                    {
                        lua_insert(L, -2);
                        lua_call(L, 1, 1);

                    }
                    if (lua_isstring(L, i))
                    {
                        const char* pStr = lua_tolstring(L, i, nullptr);
                        luaStrValue = pStr ? pStr : "<unknown>";
                    }
                    else
                    {
                        luaStrValue = "<unknown>";
                    }
                    break;
                }
                
                if (num == 1)
                    Pyx::PyxContext::GetInstance().Log(L"[%s] %s", pScript->GetName().c_str(), Pyx::Utility::String::utf8_decode(luaStrValue).c_str());
                else
                    Pyx::PyxContext::GetInstance().Log(L"[%s] [%d] %s", pScript->GetName().c_str(), i, Pyx::Utility::String::utf8_decode(luaStrValue).c_str());
            }
        }
        
        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {
            LuaIntf::LuaBinding(pScript->GetLuaState()).addFunction("print", [pScript](lua_State* L) { lua_Print(pScript, L); });
        }

    }
}
