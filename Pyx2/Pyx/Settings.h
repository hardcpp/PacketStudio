#pragma once
#include <string>
#include <vector>

namespace Pyx
{
    class PyxContext;
    class Settings
    {

    public:
        PyxContext* m_pPyxContext;
        bool OverlayInputLock = false;

    public:
        explicit Settings(PyxContext* pPyxContext);
        virtual const PyxContext* GetPyxContext() const final { return m_pPyxContext; }
        virtual bool SaveToXml(const std::wstring& fileName) const final;
        virtual bool LoadFromXml(const std::wstring& fileName) final;

    };
}
