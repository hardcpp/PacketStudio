#pragma once
#include <Pyx/Scripting/Script.h>
#include <Shlwapi.h>

namespace LuaModules
{
    namespace Pyx_FileSystem
    {

        inline void lua_WriteFile(Pyx::Scripting::Script* script, const std::wstring file, const std::wstring content)
        {

            std::wstringstream ssFile;
            ssFile << script->GetScriptDirectory() << L"\\" << file;

            wchar_t fileDirectory[MAX_PATH];
            ssFile.str().copy(fileDirectory, MAX_PATH);
            PathRemoveFileSpecW(fileDirectory);

            CreateDirectoryW(fileDirectory, nullptr);

            std::wofstream myfile(ssFile.str(), std::ios::out);

            if (myfile &&
                myfile.is_open())
            {
                myfile << content;
                myfile.close();
            }

        }

        inline std::wstring lua_ReadFile(Pyx::Scripting::Script* script, const std::wstring file)
        {

            std::wstring content;
            std::wstringstream ssFile;
            ssFile << script->GetScriptDirectory() << L"\\" << file;
            std::wifstream  myfile(ssFile.str(), std::ios::in);
            myfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

            if (myfile &&
                myfile.is_open())
            {
                std::wstringstream wss;
                wss << myfile.rdbuf();
                content = wss.str();
                myfile.close();
            }

            return content;

        }

        inline std::vector<std::wstring> lua_GetFiles(Pyx::Scripting::Script* script, const std::wstring directory)
        {
            std::vector<std::wstring> result;

            WIN32_FIND_DATA ffd;
            HANDLE hFind = INVALID_HANDLE_VALUE;
            DWORD dwError = 0;

            hFind = FindFirstFileW(std::wstring(script->GetScriptDirectory() + L"\\" + directory).c_str(), &ffd);

            if (INVALID_HANDLE_VALUE == hFind)
                return result;

            do
            {
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    result.push_back(ffd.cFileName);
                }
            } while (FindNextFileW(hFind, &ffd) != 0);

            return result;
        }

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("FileSystem")
                .addFunction("WriteFile", [pScript](const std::wstring file, const std::wstring content) { lua_WriteFile(pScript, file, content); })
                .addFunction("ReadFile", [pScript](const std::wstring file) { return lua_ReadFile(pScript, file); })
                .addFunction("GetFiles", [pScript](const std::wstring directory) { return lua_GetFiles(pScript, directory); });

        }

    }
}
