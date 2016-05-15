#pragma once
#include <set>
#include <Pyx/Scripting/Script.h>

namespace Pyx
{
    class PyxContext;
    namespace Scripting
    {
        class Script;
        class ScriptingContext
        {

        public:
            typedef void OnStartScriptCallback(Script* script);

        public:
            static ScriptingContext& GetInstance();

        private:
            std::set<Script*> m_scripts;
            Utility::Callbacks<OnStartScriptCallback> m_OnStartScriptCallbacks;

        public:
            explicit ScriptingContext();
            ~ScriptingContext();
            void Initialize();
            void Shutdown();
            void ReloadScripts();
            std::set<Script*> GetScripts() const { return m_scripts; }
            Utility::Callbacks<OnStartScriptCallback>& GetOnStartScriptCallbacks() { return m_OnStartScriptCallbacks; };
            template<typename... Args>
            void FireCallbacks(const std::wstring& name, Args&&... args)
            {
                for (Script* pScript : m_scripts)
                {
                    if (pScript->IsRunning())
                    {
                        pScript->FireCallback(name, std::forward<Args>(args)...);
                    }
                }
            }

        };
    }
}
