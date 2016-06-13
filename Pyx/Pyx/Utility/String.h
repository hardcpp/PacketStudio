#pragma once
#include "XorString.h"
#include <cstdlib>
#include <string>
#include <locale>
#include <codecvt>

namespace Pyx
{
    namespace Utility
    {
        class String
        {

        public:
            static std::string GetRandomString(int length)
            {
                std::string result;
                result.resize(length);
                const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                for (int i = 0; i < length; i++)
                    result[i] = alphanum[rand() % sizeof(alphanum) - 1];
                return result;
            }

            static std::string utf8_encode(const std::wstring &wstr)
            {
                if (wstr.empty()) return std::string();
                int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
                std::string strTo(size_needed, 0);
                WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
                return strTo;
            }

            static std::wstring utf8_decode(const std::string &str)
            {
                if (str.empty()) return std::wstring();
                int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
                std::wstring wstrTo(size_needed, 0);
                MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
                return wstrTo;
            }

        };
    }
}
