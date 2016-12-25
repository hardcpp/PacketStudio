#pragma once
#include <Pyx/Patch/IPatch.h>

namespace Pyx
{
    namespace Patch
    {
        class PatchContext;
        template<typename T>
        class IHook : public IPatch
        {

        public:
            explicit IHook(PatchContext* pPatchContext) : IPatch(pPatchContext) { }
            virtual ~IHook() { }
            virtual T GetTrampoline() const = 0;

        };
    }
}
