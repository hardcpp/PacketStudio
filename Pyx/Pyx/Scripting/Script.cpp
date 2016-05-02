#include "Script.h"
#include <Pyx/PyxContext.h>
#include "ScriptDef.h"
#include "ScriptingContext.h"
#include "LuaModules/Override.h"
#include <Shlwapi.h>
#include "LuaModules/Pyx_Scripting.h"
#include "LuaModules/Pyx_FileSystem.h"


Pyx::Scripting::Script::Script(const std::wstring& name, const std::wstring& defFileName)
 : m_name(name), m_defFileName(defFileName)
{
    wchar_t buffer[MAX_PATH];
    m_defFileName.copy(buffer, MAX_PATH);
    PathRemoveFileSpecW(buffer);
    m_directory = std::wstring(buffer) + std::wstring(L"\\");
}

Pyx::Scripting::Script::~Script()
{
    m_luaState.close();
}

void Pyx::Scripting::Script::Stop(bool fireEvent)
{
    if (IsRunning())
    {
        PyxContext::GetInstance().Log(L"Stopping script \"%s\" ...", m_name);
        if (fireEvent) FireCallback(L"Pyx.OnScriptStop");
        m_isRunning = false;
        m_callbacks.clear();
    }
}

void Pyx::Scripting::Script::Start()
{
    if (!IsRunning())
    {

        DWORD dwAttrib = GetFileAttributesW(m_defFileName.c_str());
        if (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
        {

            ScriptDef scriptDef(m_defFileName);
            std::wstring errorMessage;
            if (scriptDef.Validate(errorMessage))
            {

                PyxContext::GetInstance().Log(L"Starting script \"%s\" ...", m_name);
                m_luaState = LuaState(luaL_newstate());
                m_luaState.openLibs();

                LuaModules::Override::BindToScript(this);
                LuaModules::Pyx_Scripting::BindToScript(this);
                LuaModules::Pyx_FileSystem::BindToScript(this);

                ScriptingContext::GetInstance().GetOnStartScriptCallbacks().Run(*this);
                m_isRunning = true;

                if (scriptDef.Run(m_luaState))
                    FireCallback(L"Pyx.OnScriptStart");
                else
                    m_isRunning = false;

            }
            else
            {
                PyxContext::GetInstance().Log(L"Error starting script \"%s\"", m_name);
                PyxContext::GetInstance().Log(errorMessage);
            }

        }
    }
}

void Pyx::Scripting::Script::RegisterCallback(const std::wstring& name, LuaRef func)
{
    if (m_callbacks.find(name) == m_callbacks.end())
        m_callbacks.insert(make_pair(name, std::vector<LuaRef>()));
    m_callbacks[name].push_back(func);
}

void Pyx::Scripting::Script::UnregisterCallback(const std::wstring& name, LuaRef func)
{
    for (auto& pair : m_callbacks)
    {
        for (int i = 0; i < pair.second.size(); i++)
        {
            if (pair.first == name && pair.second[i].isIdenticalTo(func))
            {
                pair.second.erase(pair.second.begin() + i);
                return;
            }
        }
    }
}
