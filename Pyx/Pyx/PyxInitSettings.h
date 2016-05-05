#pragma once
#include <string>
#include <Pyx/Pyx.h>

namespace Pyx
{
    struct PyxInitSettings
    {
        Pyx::GuiType GuiType = Pyx::GuiType::ImGui;
        std::wstring RootDirectory = L"";
        bool GuiBlockInput = false;
        bool LogToFile = true;
        std::wstring LogDirectory = L"\\Logs";
        std::wstring ScriptsDirectory = L"\\Scripts";
    };
}
