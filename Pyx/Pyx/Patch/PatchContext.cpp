#include "PatchContext.h"
#include "../../MinHook/include/MinHook.h"

Pyx::Patch::PatchContext::PatchContext(PyxContext* pPyxContext)
    : m_pPyxContext(pPyxContext)
{
    PYX_ASSERT_A(MH_Initialize() == MH_OK);
}

Pyx::Patch::PatchContext::~PatchContext()
{

    for (auto* pPatch : m_patches)
        delete pPatch;

    m_patches.clear();

    PYX_ASSERT_A(MH_Uninitialize() == MH_OK);

}
