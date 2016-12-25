#pragma once
#include <Windows.h>
#include <string>
#include <vector>

namespace Pyx
{
    namespace Utility
    {
        class IniFile
        {

        public:
            struct SectionValue
            {
                std::wstring Section;
                std::wstring Key;
                std::wstring Value;
            };
            
        private:
            std::wstring m_fileName;

        public:
            IniFile(const std::wstring& fileName) : m_fileName(fileName) { }
            std::vector<SectionValue> GetSectionValues( const std::wstring& sectionName) const
            {
                std::vector<SectionValue> results;

                wchar_t buffer[4096];
                int charsRead = 0;
                charsRead = GetPrivateProfileSectionW(sectionName.c_str(), buffer, sizeof(buffer), m_fileName.c_str());
                if (0 < charsRead && sizeof(buffer) - 2 > charsRead) 
                {
                    const wchar_t* pSubstr = buffer;
                    while (L'\0' != *pSubstr) {
                        size_t substrLen = wcslen(pSubstr);
                        const wchar_t* pos = wcschr(pSubstr, '=');
                        if (pos) 
                        {
                            wchar_t name[256] = L"";
                            wchar_t value[256] = L"";
                            wcsncpy_s(name, _countof(name), pSubstr, pos - pSubstr);
                            wcsncpy_s(value, _countof(value), pos + 1, substrLen - (pos - pSubstr));
                            results.push_back(SectionValue{ sectionName, name, value });
                        }

                        pSubstr += (substrLen + 1);
                    }
                }
                return results;
            }

        };
    }
}
