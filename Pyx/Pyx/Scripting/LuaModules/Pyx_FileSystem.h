#pragma once
#include <Pyx/Scripting/Script.h>
#include <Shlwapi.h>

namespace LuaModules
{
    namespace Pyx_FileSystem
    {

        inline void lua_WriteFile(Pyx::Scripting::Script* script, const std::string file, const std::string content)
        {

            std::wstringstream ssFile;
            ssFile << script->GetScriptDirectory() << L"\\" << Pyx::Utility::String::utf8_decode(file);

            wchar_t fileDirectory[MAX_PATH];
            ssFile.str().copy(fileDirectory, MAX_PATH);
            PathRemoveFileSpecW(fileDirectory);

            CreateDirectoryW(fileDirectory, nullptr);

            std::ofstream myfile(ssFile.str(), std::ios::out);

            if (myfile &&
                myfile.is_open())
            {
                myfile << content;
                myfile.close();
            }

        }

        inline std::string lua_ReadFile(Pyx::Scripting::Script* script, const std::string file)
        {

            std::string content;
            std::wstringstream ssFile;
            ssFile << script->GetScriptDirectory() << L"\\" << Pyx::Utility::String::utf8_decode(file);
            std::ifstream  myfile(ssFile.str(), std::ios::in);
            myfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

            if (myfile &&
                myfile.is_open())
            {
                std::stringstream ss;
                ss << myfile.rdbuf();
                content = ss.str();
                myfile.close();
            }

            return content;

        }

        inline std::vector<std::string> lua_GetFiles(Pyx::Scripting::Script* script, const std::string directory)
        {
            std::vector<std::string> result;

            WIN32_FIND_DATA ffd;
            HANDLE hFind = INVALID_HANDLE_VALUE;
            DWORD dwError = 0;

            hFind = FindFirstFileW(std::wstring(script->GetScriptDirectory() + L"\\" + Pyx::Utility::String::utf8_decode(directory)).c_str(), &ffd);

            if (INVALID_HANDLE_VALUE == hFind)
                return result;

            do
            {
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && ffd.cFileName)
                {
                    result.push_back(Pyx::Utility::String::utf8_encode(ffd.cFileName));
                }
            } while (FindNextFileW(hFind, &ffd) != 0);

            return result;
        }

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule(XorStringA("FileSystem"))
                .addFunction(XorStringA("WriteFile"), [pScript](const std::string file, const std::string content) { lua_WriteFile(pScript, file, content); })
                .addFunction(XorStringA("ReadFile"), [pScript](const std::string file) { return lua_ReadFile(pScript, file); })
                .addFunction(XorStringA("GetFiles"), [pScript](const std::string directory) { return lua_GetFiles(pScript, directory); });

        }

    }
}
