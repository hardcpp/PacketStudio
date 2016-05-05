#include <Pyx/Graphics/GuiContext.h>
#include <Pyx/PyxContext.h>
#include "Gui/ImGuiImpl.h"

Pyx::Graphics::GuiContext& Pyx::Graphics::GuiContext::GetInstance()
{
    static GuiContext ctx;
    return ctx;
}

Pyx::Graphics::GuiContext::GuiContext()
{

}

Pyx::Graphics::GuiContext::~GuiContext()
{

}

void Pyx::Graphics::GuiContext::Shutdown()
{

    if (m_pGui)
    {
        m_pGui->Shutdown();
        delete m_pGui;
        m_pGui = nullptr;
    }

}

Pyx::Graphics::Gui::IGui* Pyx::Graphics::GuiContext::GetGui()
{
    if (m_pGui == nullptr)
    {
        switch (PyxContext::GetInstance().GetSettings().GuiType)
        {
        case GuiType::ImGui:
            m_pGui = new Gui::ImGuiImpl();
            PyxContext::GetInstance().Log("[Gui] Using gui : %s", m_pGui->GetGuiTypeString());
            break;
        default:
            break;
        }
    }
    return m_pGui;
}
