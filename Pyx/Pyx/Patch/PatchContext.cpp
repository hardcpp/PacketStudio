#include <Pyx/Patch/PatchContext.h>

Pyx::Patch::PatchContext& Pyx::Patch::PatchContext::GetInstance()
{
    static PatchContext ctx;
    return ctx;
}

Pyx::Patch::PatchContext::PatchContext()
{
}

Pyx::Patch::PatchContext::~PatchContext()
{

}

void Pyx::Patch::PatchContext::Initialize()
{
    PYX_ASSERT_A(MH_Initialize() == MH_OK);
}

void Pyx::Patch::PatchContext::Shutdown()
{

    for (auto* pPatch : m_patches)
        delete pPatch;

    m_patches.clear();

    PYX_ASSERT_A(MH_Uninitialize() == MH_OK);

}
