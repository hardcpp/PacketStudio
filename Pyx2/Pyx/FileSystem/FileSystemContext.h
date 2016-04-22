#pragma once
#include <string>

namespace Pyx
{
    class PyxContext;
    namespace FileSystem
    {
        class FileSystemContext
        {

        private:
            PyxContext* m_pPyxContext;
            std::wstring m_rootDirectory;

        public:
            explicit FileSystemContext(PyxContext* pPyxContext);
            ~FileSystemContext() { }
            virtual const PyxContext* GetPyxContext() const { return m_pPyxContext; }
            virtual const std::wstring& GetRootDirectory() const { return m_rootDirectory; }
            virtual bool FileExists(const std::string& fileName) const;
            virtual bool FileExists(const std::wstring& fileName) const;
            
        };
    }
}
