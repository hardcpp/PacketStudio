#pragma once
#include <set>
#include "Detour.h"

namespace Pyx
{
    class PyxContext;
    namespace Patch
    {
        class PatchContext
        {

        private:
            PyxContext* m_pPyxContext;
            std::set<IPatch*> m_patches;

        public:
            explicit PatchContext(PyxContext* pPyxContext);
            ~PatchContext();
            PyxContext* GetPyxContext() const { return m_pPyxContext; }
            template<typename T> Detour<T>* CreateDetour(T target, T detour)
            {
                auto pDetour = new Detour<T>(this, target, detour);
                m_patches.insert(pDetour);
                return pDetour;
            }
            template<typename T> bool CreateAndApplyDetour(T target, T detour, Detour<T>** ppDetour)
            {
                auto pDetour = CreateDetour(target, detour);
                if (pDetour)
                {
                    *ppDetour = pDetour;
                    pDetour->Apply();
                    return true;
                }
                return false;
            }
            template<typename T> bool RemoveDetour(Detour<T>* pDetour)
            {
                if (pDetour)
                {
                    pDetour->Remove();
                    m_patches.erase(pDetour);
                    delete pDetour;
                    return true;
                }
                return false;
            }

        };
    }
}
