#include <zenxml/xml.h>
#include "PyxContext.h"
#include "Settings.h"

Pyx::Settings::Settings(PyxContext* pPyxContext)
    : m_pPyxContext(pPyxContext)
{

    PYX_ASSERT_A(pPyxContext != nullptr);

}

bool Pyx::Settings::SaveToXml(const std::wstring& fileName) const
{

    zen::XmlDoc doc;
    zen::XmlOut out(doc);

    out[XorStringA("OverlayInputLock")](OverlayInputLock);

    try
    {
        zen::save(doc, fileName);
        return true;
    }
    catch (const zen::XmlFileError&)
    {
        return false;
    }

}

bool Pyx::Settings::LoadFromXml(const std::wstring& fileName)
{

    if (!m_pPyxContext->GetFileSystemContext()->FileExists(fileName))
    {
        return false;
    }

    zen::XmlDoc doc;

    try
    {
        doc = zen::load(fileName);  
    }
    catch (const zen::XmlError&)
    {
        return false;
    }

    zen::XmlIn in(doc);
    in[XorStringA("OverlayInputLock")](OverlayInputLock);
    
    return true;

}
