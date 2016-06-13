#include <Pyx/Patch/PatchContext.h>

bool g_mhInitialized = false;

Pyx::Patch::PatchContext& Pyx::Patch::PatchContext::GetInstance()
{
	if (!g_mhInitialized) g_mhInitialized = MH_Initialize() == MH_OK;
    static PatchContext ctx;
    return ctx;
}

Pyx::Patch::PatchContext::PatchContext()
{
}

Pyx::Patch::PatchContext::~PatchContext()
{

}

void Pyx::Patch::PatchContext::Shutdown()
{

    for (auto* pPatch : m_patches)
        delete pPatch;

    m_patches.clear();

    PYX_ASSERT_A(MH_Uninitialize() == MH_OK);

}
