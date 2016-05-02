#pragma once
#include <string>
#include <fstream>
#include <functional>
#include <map>
#include <vector>
#include <mutex>
#include "../../Lua/lua.hpp"
#include "../../Lua/LuaIntf.h"
#include "../../Lua/LuaRef.h"
#include "LuaModules/Mapping_WString.h"
#include "../PyxContext.h"

using namespace LuaIntf;

namespace LuaIntf
{
    LUA_USING_LIST_TYPE(std::vector)
    LUA_USING_MAP_TYPE(std::map)
}

namespace Pyx
{
    namespace Scripting
    {
        class Script
        {

        private:
            std::wstring m_name;
            std::wstring m_defFileName;
            std::wstring m_directory;
            bool m_isRunning = false;
            std::map<std::wstring, std::vector<LuaRef>> m_callbacks;
            LuaState m_luaState;
            std::recursive_mutex m_callbacksMutex;

        public:
            Script(const std::wstring& name, const std::wstring& defFileName);
            ~Script();
            void Stop(bool fireEvent = true);
            void Start();
            bool IsRunning() const { return m_isRunning; }
            const std::wstring& GetName() const { return m_name; }
            std::map<std::wstring, std::vector<LuaRef>>& GetCallbacks() { return m_callbacks; }
            LuaState& GetLuaState() { return m_luaState; }
            const std::wstring& GetDefFileName() const { return m_defFileName; }
            const std::wstring& GetScriptDirectory() const { return m_directory; }
            void RegisterCallback(const std::wstring& name, LuaRef func);
            void UnregisterCallback(const std::wstring& name, LuaRef func);

        public:
            template<typename... Args>
            void FireCallback(const std::wstring& name, Args&&... args)
            {
                auto find = m_callbacks.find(name);
                if (find != m_callbacks.end())
                {
                    for (auto t_func : find->second)
                    {
                        try
                        {
                            t_func.call(std::forward<Args>(args)...);
                        }
                        catch (LuaException &e)
                        {
                            PyxContext::GetInstance().Log(XorStringW(L"Error in script \"%s\""), m_name);
                            PyxContext::GetInstance().Log(e.what());
                        }
                        catch (const std::exception &e) 
                        {
                            PyxContext::GetInstance().Log(XorStringW(L"Error in script \"%s\""), m_name);
                            PyxContext::GetInstance().Log(e.what());
                        }
                    }
                }
            }

        };
    }
}