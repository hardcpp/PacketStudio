#pragma once
#include <string>
#include <Pyx/Pyx.h>
#include <vector>

namespace Pyx
{
    struct PyxInitSettings
    {
        Pyx::GuiType GuiType                            = Pyx::GuiType::ImGui;
        std::wstring RootDirectory                      = L"";
        bool GuiBlockInput                              = false;
        std::vector<int> GuiToggleVisibilityHotkeys     = { VK_INSERT };
        std::vector<int> ImGuiToggleConsoleHotkeys      = { VK_F12 };
        bool LogToFile                                  = true;
        std::wstring LogDirectory                       = XorStringW(L"\\Logs");
        std::wstring ScriptsDirectory                   = XorStringW(L"\\Scripts");
    };
}
