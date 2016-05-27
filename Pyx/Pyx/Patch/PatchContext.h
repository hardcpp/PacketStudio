#pragma once
#include <set>
#include <Pyx/Patch/Detour.h>
#include <Pyx/Patch/VmtHook.h>

namespace Pyx
{
    class PyxContext;
    namespace Patch
    {
        class PatchContext
        {

        public:
            static PatchContext& GetInstance();

        private:
            std::set<IPatch*> m_patches;

        public:
            explicit PatchContext();
            ~PatchContext();
            void Shutdown();
            template<typename T> Detour<T>* CreateDetour(T target, T detour)
            {
                auto pDetour = new Detour<T>(this, target, detour);
                m_patches.insert(pDetour);
                return pDetour;
            }
            template<typename T> VmtHook<T>* CreateVmtHook(void** ppVtable, size_t index, T detour)
            {
                auto pVmtHook = new VmtHook<T>(this, ppVtable, index, detour);
                m_patches.insert(pVmtHook);
                return pVmtHook;
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
            template<typename T> bool CreateAndApplyVmtHook(void** ppVtable, size_t index, T detour, VmtHook<T>** ppVmtHook)
            {
                auto pVmtHook = CreateVmtHook(ppVtable, index, detour);
                if (pVmtHook)
                {
                    *ppVmtHook = pVmtHook;
                    pVmtHook->Apply();
                    return true;
                }
                return false;
            }

        };
    }
}
