#include <Pyx/Scripting/ScriptDef.h>
#include <Pyx/Scripting/ScriptingContext.h>
#include <algorithm>

Pyx::Scripting::ScriptingContext& Pyx::Scripting::ScriptingContext::GetInstance()
{
    static ScriptingContext ctx;
    return ctx;
}

Pyx::Scripting::ScriptingContext::ScriptingContext()
{
}

Pyx::Scripting::ScriptingContext::~ScriptingContext()
{
}

void Pyx::Scripting::ScriptingContext::Initialize()
{
    ReloadScripts();
}

void Pyx::Scripting::ScriptingContext::Shutdown()
{
    for (auto* pScript : m_scripts)
    {
        pScript->Stop();
        delete pScript;
    }
    m_scripts.clear();
}

bool compareStudents(Pyx::Scripting::Script* a, Pyx::Scripting::Script* b) {
    return a->GetName().compare(b->GetName()) < 0;
}

void Pyx::Scripting::ScriptingContext::ReloadScripts()
{
    PyxContext::GetInstance().Log(XorStringA("[Scripting] Reloading scripts ..."));

    const auto& pyxSettings = PyxContext::GetInstance().GetSettings();

    for (auto* pScript : m_scripts)
    {
        if (pScript->IsRunning()) 
            pScript->Stop();
        delete pScript;
    }

    m_scripts.clear();

    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;
    hFind = FindFirstFileW(std::wstring(pyxSettings.RootDirectory + pyxSettings.ScriptsDirectory + XorStringW(L"\\*")).c_str(), &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
        return;

    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            auto fileName = pyxSettings.RootDirectory + pyxSettings.ScriptsDirectory + L"\\" + std::wstring(ffd.cFileName) + XorStringW(L"\\script.def");
            auto scriptName = std::wstring(ffd.cFileName);
            DWORD dwAttrib = GetFileAttributesW(fileName.c_str());
            if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
                !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
            {
                ScriptDef scriptDef{ fileName };
                if (scriptDef.IsScript())
                {
                    PyxContext::GetInstance().Log(XorStringW(L"[Scripting] Found script \"%s\""), scriptDef.GetName().c_str());
                    m_scripts.push_back(new Script(scriptDef.GetName(), fileName));
                }
            }
        }
    } while (FindNextFileW(hFind, &ffd) != 0);

    sort(m_scripts.begin(), m_scripts.end(), [](Script* a, Script* b) {
        return a->GetName().compare(b->GetName()) < 0;
    });
    
}
