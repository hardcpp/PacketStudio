#pragma once
#include <string>
#include <vector>
#include <Pyx/Scripting/Script.h>
#include <Pyx/Utility/IniFile.h>

namespace Pyx
{
    namespace Scripting
    {
        class ScriptDef
        {

        public:
            ScriptDef(std::wstring fileName);
            const std::wstring GetName();
            const std::wstring GetType();
            bool IsScript() { return GetType() == XorStringW(L"script"); }
            bool IsLib() { return GetType() == XorStringW(L"lib"); }
            std::vector<std::wstring> GetFiles();
            std::vector<std::wstring> GetDependencies();
            bool Validate(std::wstring& error);
            bool Run(LuaState& luaState);

        private:
            std::wstring m_scriptDirectory;
            std::vector<Utility::IniFile::SectionValue> m_scriptSection;
            std::vector<Utility::IniFile::SectionValue> m_filesSection;
            std::vector<Utility::IniFile::SectionValue> m_dependenciestSection;

        };
    }
}
