#pragma once
#include "IHook.h"
#include "../../MinHook/include/MinHook.h"

namespace Pyx
{
    namespace Patch
    {
        class PatchContext;
        template<typename T>
        class Detour : public IHook<T>
        {

        private:
            T m_trampoline;
            T m_target;
            T m_detour;
            bool m_isEnabled = false;

        public:
            explicit Detour<T>(PatchContext* pPatchContext, T target, T detour)
                : IHook(pPatchContext), m_target(target), m_detour(detour)
            {
                MH_CreateHook(m_target, m_detour, reinterpret_cast<void**>(&m_trampoline));
            }
            ~Detour() override
            {
                MH_DisableHook(m_target);
            }
            T GetTrampoline() const override { return static_cast<T>(m_trampoline); }
            bool IsApplied() const override { return m_isEnabled; }
            void Apply() override
            {
                m_isEnabled = !m_isEnabled && MH_EnableHook(m_target) == MH_OK;
            }
            void Remove() override
            {
                m_isEnabled = !(m_isEnabled && MH_DisableHook(m_target) == MH_OK);
            }
        };
    }
}
