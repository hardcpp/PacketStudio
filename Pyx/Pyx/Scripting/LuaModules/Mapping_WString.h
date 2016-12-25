//#pragma once
//#include <locale>
//#include <codecvt>
//#include <Pyx/PyxContext.h>
//#include <Lua/lua.hpp>
//#include <Lua/LuaIntf.h>
//#include <Pyx/Utility/String.h>
//
//namespace LuaIntf
//{
//
//    template <>
//    struct LuaTypeMapping <std::wstring>
//    {
//        static void push(lua_State* L, const std::wstring& str)
//        {
//            if (str.empty()) 
//{
//                lua_pushliteral(L, "");
//            }
//            else 
//            {
//                std::string buf = Pyx::Utility::String::utf8_encode(str);
//                lua_pushlstring(L, buf.c_str(), buf.length());
//            }
//        }
//
//        static std::wstring get(lua_State* L, int index)
//        {
//            size_t len;
//            const char* p = luaL_tolstring(L, index, &len);
//            return p ? Pyx::Utility::String::utf8_decode(p) : L"nil";
//        }
//
//        static std::wstring opt(lua_State* L, int index, const std::wstring& def)
//        {
//            return lua_isnoneornil(L, index) ? def : get(L, index);
//        }
//    };
//
//}
