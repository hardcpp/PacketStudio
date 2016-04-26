#include "GuiContext.h"
#include "../Pyx.h"
#include "Gui/ImGuiImpl.h"

Pyx::Graphics::GuiContext::GuiContext(GraphicsContext* pGraphicsContext)
    : m_pGraphicsContext(pGraphicsContext)
{
    m_pGui = new Gui::ImGuiImpl(this);
}


Pyx::Graphics::GuiContext::~GuiContext()
{

    if (m_pGui)
    {
        delete m_pGui;
        m_pGui = nullptr;
    }

}
