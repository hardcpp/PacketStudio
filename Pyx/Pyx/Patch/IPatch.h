#pragma once
#include "../PyxContext.h"

namespace Pyx
{
    namespace Patch
    {
        class PatchContext;
        class IPatch
        {

        private:
            PatchContext* m_pPatchContext;

        public:
            explicit IPatch(PatchContext* pPatchContext) : m_pPatchContext(pPatchContext) { }
            virtual ~IPatch() { }
            virtual PatchContext* GetPatchContext() const { return m_pPatchContext; }
            virtual bool IsApplied() const = 0;
            virtual void Apply() = 0;
            virtual void Remove() = 0;

        };
    }
}
