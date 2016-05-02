#include "ScriptDef.h"
#include <Shlwapi.h>
#include "../PyxContext.h"
#include "../../utf8/utf8.h"

Pyx::Scripting::ScriptDef::ScriptDef(std::wstring fileName)
{
    wchar_t buffer[MAX_PATH];
    fileName.copy(buffer, MAX_PATH);
    PathRemoveFileSpecW(buffer);
    m_scriptDirectory = std::wstring(buffer) + std::wstring(L"\\");
    auto scriptDefIni = Utility::IniFile(fileName);

    m_scriptSection = scriptDefIni.GetSectionValues(L"script");
    m_filesSection = scriptDefIni.GetSectionValues(L"files");
    m_dependenciestSection = scriptDefIni.GetSectionValues(L"dependencies");
}

const std::wstring Pyx::Scripting::ScriptDef::GetName()
{
    for (auto& value : m_scriptSection)
        if (value.Key == L"name")
            return value.Value;
    return L"";
}

const std::wstring Pyx::Scripting::ScriptDef::GetType()
{
    for (auto& value : m_scriptSection)
        if (value.Key == L"type")
            return value.Value;
    return L"";
}

std::vector<std::wstring> Pyx::Scripting::ScriptDef::GetFiles()
{
    std::vector<std::wstring> result;
    for (auto& value : m_filesSection)
        if (value.Key == L"file")
        {
            std::wstring pathName = m_scriptDirectory + value.Value;
            wchar_t fullPathName[MAX_PATH];
            GetFullPathNameW(pathName.c_str(), MAX_PATH, fullPathName, nullptr);
            result.push_back(fullPathName);
        }
    return result;
}

std::vector<std::wstring> Pyx::Scripting::ScriptDef::GetDependencies()
{
    std::vector<std::wstring> result;
    for (auto& value : m_dependenciestSection)
        if (value.Key == L"file")
        {
            std::wstring pathName = m_scriptDirectory + value.Value;
            wchar_t fullPathName[MAX_PATH];
            GetFullPathNameW(pathName.c_str(), MAX_PATH, fullPathName, nullptr);
            result.push_back(fullPathName);
        }
    return result;
}

bool Pyx::Scripting::ScriptDef::Validate(std::wstring& error)
{

    for (auto dep : GetDependencies())
    {

        DWORD dwAttrib = GetFileAttributesW(dep.c_str());
        if (dwAttrib == INVALID_FILE_ATTRIBUTES || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
        {
            ScriptDef def{ dep };
            if (!def.Validate(error))
                return false;
        }
        else
        {
            error = L"[" + GetName() + L"] File not found : " + dep;
            return false;
        }
    }

    for (auto file : GetFiles())
    {
        DWORD dwAttrib = GetFileAttributesW(file.c_str());
        if (dwAttrib == INVALID_FILE_ATTRIBUTES || (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
        {
            error = L"[" + GetName() + L"] File not found : " + file;
            return false;
        }
    }

    return true;

}

bool Pyx::Scripting::ScriptDef::Run(LuaIntf::LuaState& luaState)
{
    for (auto dep : GetDependencies())
    {
        ScriptDef def{ dep };
        if (!def.Run(luaState))
        {
            return false;
        }
    }

    for (auto file : GetFiles())
    {
        try
        {
            std::fstream fs;
            fs.open(file, std::ios::in);
            std::string content((std::istreambuf_iterator<char>(fs)), (std::istreambuf_iterator<char>()));
            if (luaState.doString(content.c_str()))
            {
                PyxContext::GetInstance().Log(L"Error fin file : \"" + file + L"\" :");
                std::string error = luaState.getString(-1);
                std::wstring utf16Error;
                utf8::utf8to16(error.begin(), error.end(), utf16Error.begin());
                PyxContext::GetInstance().Log(utf16Error);
                return false;
            }
        }
        catch (const std::exception &e) {
            PyxContext::GetInstance().Log(L"Error fin file : \"" + file + L"\" :");
            PyxContext::GetInstance().Log(e.what());
            return false;
        }

    }

    return true;
}
