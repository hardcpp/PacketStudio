#pragma once
#include <string>
#include <Pyx/Pyx.h>
#include <vector>

namespace Pyx
{
    struct PyxInitSettings
    {
        Pyx::GuiType GuiType = Pyx::GuiType::ImGui;
        std::wstring RootDirectory = L"";
        bool GuiBlockInput = false;
		std::vector<int> GuiToggleVisibilityHotkeys = { VK_INSERT };
        bool LogToFile = true;
        std::wstring LogDirectory = L"\\Logs";
        std::wstring ScriptsDirectory = L"\\Scripts";
    };
}
