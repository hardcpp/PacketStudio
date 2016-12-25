#pragma once
#include <Pyx/Patch/IHook.h>

namespace Pyx
{
    namespace Patch
    {
        class PatchContext;
        template<typename T>
        class VmtHook : public IHook<T>
        {

        private:
            void** m_ppVtable;
            size_t m_index;
            T m_original;
            T m_detour;

        public:
            explicit VmtHook<T>(PatchContext* pPatchContext, void** ppVtable, size_t index, T detour)
                : IHook(pPatchContext), m_ppVtable(ppVtable), m_index(index), m_detour(detour)
            {
                m_original = (T)ppVtable[index];
            }
            ~VmtHook() override
            {
                Remove();
            }
            T GetTrampoline() const override { return m_original; }
            bool IsApplied() const override { return m_ppVtable[m_index] == m_detour; }
            void Apply() override
            {
                DWORD oldProtect;
                VirtualProtect(&m_ppVtable[m_index], sizeof(T), PAGE_READWRITE, &oldProtect);
                m_ppVtable[m_index] = m_detour;
                VirtualProtect(&m_ppVtable[m_index], sizeof(T), oldProtect, &oldProtect);
            }
            void Remove() override
            {
                DWORD oldProtect;
                VirtualProtect(&m_ppVtable[m_index], sizeof(T), PAGE_READWRITE, &oldProtect);
                m_ppVtable[m_index] = m_original;
                VirtualProtect(&m_ppVtable[m_index], sizeof(T), oldProtect, &oldProtect);
            }
            void** GetVtable() const { return m_ppVtable; }
            void SetVtable(void** ppVtable) { m_ppVtable = ppVtable; m_original = (T)m_ppVtable[m_index]; }
            void SetVtableAndApply(void** ppVtable) { SetVtable(ppVtable); Apply(); }
        };
    }
}
