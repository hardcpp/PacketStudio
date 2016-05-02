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
            char m_hookBuffer[20];

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
                if (!m_isEnabled)
                {
                    m_isEnabled = MH_EnableHook(m_target) == MH_OK;
                    if (m_isEnabled)
                        memcpy(m_hookBuffer, m_target, sizeof(m_hookBuffer));
                }
            }
            
            void Remove() override
            {
                m_isEnabled = !(m_isEnabled && MH_DisableHook(m_target) == MH_OK);
            }
            void EnsureApply()
            {
                if (memcmp(m_hookBuffer, m_target, sizeof(m_hookBuffer)) != 0)
                {
                    DWORD oldProtect;
                    VirtualProtect(m_target, sizeof(m_hookBuffer), PAGE_READWRITE, &oldProtect);
                    memcpy(m_target, m_hookBuffer, sizeof(m_hookBuffer));
                    VirtualProtect(m_target, sizeof(T), oldProtect, &oldProtect);
                }
            }
        };
    }
}
