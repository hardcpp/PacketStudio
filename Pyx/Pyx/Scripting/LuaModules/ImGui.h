#pragma once
#include <Pyx/Scripting/Script.h>
#include <ImGui/imgui.h>    

#define _def_float(f) _def<float, long((f) * 1000000), 1000000>

namespace LuaModules
{
    namespace ImGuiLua
    {

        using namespace LuaIntf;


        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState())
                .beginClass<ImVec2>(XorStringA("ImVec2"))
                .addConstructor(LUA_ARGS(_def_float(0.0f), _def_float(0.0f)))
                .addVariable("x", &ImVec2::x)
                .addVariable("y", &ImVec2::y)
                .endClass();

            LuaBinding(pScript->GetLuaState())
                .beginClass<ImVec4>(XorStringA("ImVec4"))
                .addConstructor(LUA_ARGS(_def_float(0.0f), _def_float(0.0f), _def_float(0.0f), _def_float(0.0f)))
                .addVariable("x", &ImVec4::x)
                .addVariable("y", &ImVec4::y)
                .addVariable("z", &ImVec4::z)
                .addVariable("w", &ImVec4::w)
                .endClass();

            auto module = LuaBinding(pScript->GetLuaState()).beginModule(XorStringA("ImGui"));

            /*
            Window
            */

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoTitleBar);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoResize);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoMove);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoScrollbar);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoScrollWithMouse);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_AlwaysAutoResize);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_ShowBorders);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoSavedSettings);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoInputs);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_MenuBar);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_HorizontalScrollbar);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoFocusOnAppearing);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiWindowFlags_NoBringToFrontOnFocus);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CharsDecimal);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CharsHexadecimal);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CharsUppercase);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CharsNoBlank);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_AutoSelectAll);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_EnterReturnsTrue);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CallbackCompletion);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CallbackHistory);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CallbackAlways);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CallbackCharFilter);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_AllowTabInput);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_CtrlEnterForNewLine);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_NoHorizontalScroll);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_AlwaysInsertMode);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_ReadOnly);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiInputTextFlags_Password);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSelectableFlags_DontClosePopups);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSelectableFlags_SpanAllColumns);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Tab);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_LeftArrow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_RightArrow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_UpArrow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_DownArrow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_PageUp);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_PageDown);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Home);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_End);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Delete);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Backspace);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Enter);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Escape);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_A);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_C);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_V);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_X);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Y);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiKey_Z);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_Text);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_TextDisabled);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_WindowBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ChildWindowBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_Border);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_BorderShadow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_FrameBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_FrameBgHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_FrameBgActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_TitleBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_TitleBgCollapsed);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_TitleBgActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_MenuBarBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ScrollbarBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ScrollbarGrab);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ScrollbarGrabHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ScrollbarGrabActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ComboBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_CheckMark);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_SliderGrab);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_SliderGrabActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_Button);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ButtonHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ButtonActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_Header);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_HeaderHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_HeaderActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_Column);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ColumnHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ColumnActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ResizeGrip);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ResizeGripHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ResizeGripActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_CloseButton);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_CloseButtonHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_CloseButtonActive);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_PlotLines);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_PlotLinesHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_PlotHistogram);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_PlotHistogramHovered);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_TextSelectedBg);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiCol_ModalWindowDarkening);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_Alpha);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_WindowPadding);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_WindowRounding);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_WindowMinSize);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_ChildWindowRounding);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_FramePadding);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_FrameRounding);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_ItemSpacing);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_ItemInnerSpacing);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_IndentSpacing);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiStyleVar_GrabMinSize);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_Left);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_Center);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_Right);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_Top);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_VCenter);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiAlign_Default);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_Arrow);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_TextInput);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_Move);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_ResizeNS);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_ResizeEW);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_ResizeNESW);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiMouseCursor_ResizeNWSE);

            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSetCond_Always);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSetCond_Once);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSetCond_FirstUseEver);
            LUAINTF_ADD_ENUM_VALUE(pScript->GetLuaState(), ImGuiSetCond_Appearing);

            module.addFunction(XorStringA("Begin"), [](std::string name) { return ImGui::Begin(name.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("Begin"), [](std::string name, bool& opened, int flags = 0) { return ImGui::Begin(name.c_str(), (bool*)&opened, flags); }, LUA_ARGS(std::string, _ref<bool&>, _opt<int>));
            module.addFunction(XorStringA("Begin"), [](std::string name, bool& opened, ImVec2 size, float alpha, int flags) { return ImGui::Begin(name.c_str(), (bool*)&opened, size, alpha, flags); }, LUA_ARGS(std::string, _ref<bool&>, _opt<ImVec2>, _def_float(-1.0f), _def<int, 0>));
            module.addFunction(XorStringA("End"), &ImGui::End);
            module.addFunction(XorStringA("BeginChild"), [](std::string name, ImVec2 size, bool border, int extra_flags) { return ImGui::BeginChild(name.c_str(), size, border, extra_flags); }, LUA_ARGS(std::string, _opt<ImVec2>, _def<bool, false>, _def<int, 0>));
            module.addFunction(XorStringA("BeginChild"), [](int id, ImVec2 size, bool border, int extra_flags) { return ImGui::BeginChild(id, size, border, extra_flags); }, LUA_ARGS(int, _opt<ImVec2>, _def<bool, false>, _def<int, 0>));
            module.addFunction(XorStringA("EndChild"), &ImGui::EndChild);
            module.addFunction(XorStringA("GetContentRegionMax"), &ImGui::GetContentRegionMax);
            module.addFunction(XorStringA("GetContentRegionAvail"), &ImGui::GetContentRegionAvail);
            module.addFunction(XorStringA("GetContentRegionAvailWidth"), &ImGui::GetContentRegionAvailWidth);
            module.addFunction(XorStringA("GetWindowContentRegionMin"), &ImGui::GetWindowContentRegionMin);
            module.addFunction(XorStringA("GetWindowContentRegionMax"), &ImGui::GetWindowContentRegionMax);
            module.addFunction(XorStringA("GetWindowContentRegionWidth"), &ImGui::GetWindowContentRegionWidth);
            // TODO : GetWindowDrawList
            // TODO : GetWindowFont
            module.addFunction(XorStringA("GetWindowFontSize"), &ImGui::GetWindowFontSize);
            module.addFunction(XorStringA("SetWindowFontScale"), &ImGui::SetWindowFontScale);
            module.addFunction(XorStringA("GetWindowPos"), &ImGui::GetWindowPos);
            module.addFunction(XorStringA("GetWindowSize"), &ImGui::GetWindowSize);
            module.addFunction(XorStringA("GetWindowWidth"), &ImGui::GetWindowWidth);
            module.addFunction(XorStringA("GetWindowHeight"), &ImGui::GetWindowHeight);
            module.addFunction(XorStringA("IsWindowCollapsed"), &ImGui::IsWindowCollapsed);

            module.addFunction(XorStringA("SetNextWindowPos"), [](ImVec2 pos, int cond) { return ImGui::SetNextWindowPos(pos, cond); }, LUA_ARGS(ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetNextWindowPosCenter"), [](int cond) { return ImGui::SetNextWindowPosCenter(cond); }, LUA_ARGS(_def<int, 0>));
            module.addFunction(XorStringA("SetNextWindowSize"), [](ImVec2 size, int cond) { return ImGui::SetNextWindowSize(size, cond); }, LUA_ARGS(ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetNextWindowContentSize"), [](ImVec2 size) { return ImGui::SetNextWindowContentSize(size); }, LUA_ARGS(ImVec2));
            module.addFunction(XorStringA("SetNextWindowContentWidth"), &ImGui::SetNextWindowContentWidth);
            module.addFunction(XorStringA("SetNextWindowCollapsed"), [](bool collapsed, int cond) { return ImGui::SetNextWindowCollapsed(collapsed, cond); }, LUA_ARGS(bool, _def<int, 0>));
            module.addFunction(XorStringA("SetNextWindowFocus"), &ImGui::SetNextWindowFocus);
            module.addFunction(XorStringA("SetWindowPos"), [](ImVec2 pos, int cond) { return ImGui::SetWindowPos(pos, cond); }, LUA_ARGS(ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowSize"), [](ImVec2 size, int cond) { return ImGui::SetWindowSize(size, cond); }, LUA_ARGS(ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowCollapsed"), [](bool collapsed, int cond) { return ImGui::SetWindowCollapsed(collapsed, cond); }, LUA_ARGS(bool, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowFocus"), []() { return ImGui::SetWindowFocus(); });
            module.addFunction(XorStringA("SetWindowPos"), [](std::string name, ImVec2 pos, int cond) { return ImGui::SetWindowPos(name.c_str(), pos, cond); }, LUA_ARGS(std::string, ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowSize"), [](std::string name, ImVec2 size, int cond) { return ImGui::SetWindowSize(name.c_str(), size, cond); }, LUA_ARGS(std::string, ImVec2, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowCollapsed"), [](std::string name, bool collapsed, int cond) { return ImGui::SetWindowCollapsed(name.c_str(), collapsed, cond); }, LUA_ARGS(std::string, bool, _def<int, 0>));
            module.addFunction(XorStringA("SetWindowFocus"), [](std::string name) { return ImGui::SetWindowFocus(name.c_str()); }, LUA_ARGS(std::string));

            module.addFunction(XorStringA("GetScrollX"), &ImGui::GetScrollX);
            module.addFunction(XorStringA("GetScrollY"), &ImGui::GetScrollY);
            module.addFunction(XorStringA("GetScrollMaxX"), &ImGui::GetScrollMaxX);
            module.addFunction(XorStringA("GetScrollMaxY"), &ImGui::GetScrollMaxY);
            module.addFunction(XorStringA("SetScrollX"), &ImGui::SetScrollX);
            module.addFunction(XorStringA("SetScrollY"), &ImGui::SetScrollY);
            module.addFunction(XorStringA("SetScrollHere"), [](float center_y_ratio) { return ImGui::SetScrollHere(center_y_ratio); }, LUA_ARGS(_def_float(0.5f)));
            module.addFunction(XorStringA("SetScrollFromPosY"), [](float pos_y, float center_y_ratio) { return ImGui::SetScrollFromPosY(pos_y, center_y_ratio); }, LUA_ARGS(float, _def_float(0.5f)));
            module.addFunction(XorStringA("SetKeyboardFocusHere"), [](int offset) { return ImGui::SetKeyboardFocusHere(offset); }, LUA_ARGS(_def<int, 0>));
            // TODO : SetStateStorage
            // TODO : GetStateStorage

            /*
            TODO : Parameters stacks (shared)
            */

            /*
            TODO : Parameters stacks (current window)
            */
            module.addFunction(XorStringA("PushItemWidth"), &ImGui::PushItemWidth);
            module.addFunction(XorStringA("PopItemWidth"), &ImGui::PopItemWidth);
            module.addFunction(XorStringA("CalcItemWidth"), &ImGui::CalcItemWidth);

            /*
            Cursor / Layout
            */


            module.addFunction(XorStringA("BeginGroup"), &ImGui::BeginGroup);
            module.addFunction(XorStringA("EndGroup"), &ImGui::EndGroup);
            module.addFunction(XorStringA("Separator"), &ImGui::Separator);
            module.addFunction(XorStringA("SameLine"), [](float local_pos_x, float spacing_w) { return ImGui::SameLine(local_pos_x, spacing_w); }, LUA_ARGS(_def_float(0.0f), _def_float(-1.0f)));
            module.addFunction(XorStringA("Spacing"), &ImGui::Spacing);
            module.addFunction(XorStringA("Dummy"), [](ImVec2 size) { return ImGui::Dummy(size); }, LUA_ARGS(ImVec2));
            module.addFunction(XorStringA("Indent"), &ImGui::Indent);
            module.addFunction(XorStringA("Unindent"), &ImGui::Unindent);
            module.addFunction(XorStringA("Columns"), [](int count, std::string id, bool border) { return ImGui::Columns(count, id.c_str(), border); }, LUA_ARGS(_def<int, 0>, _opt<std::string>, _def<bool, true>));
            module.addFunction(XorStringA("NextColumn"), &ImGui::NextColumn);
            module.addFunction(XorStringA("GetColumnIndex"), &ImGui::GetColumnIndex);
            module.addFunction(XorStringA("GetColumnOffset"), [](int column_index) { return ImGui::GetColumnOffset(column_index); }, LUA_ARGS(_def<int, -1>));
            module.addFunction(XorStringA("SetColumnOffset"), [](int column_index, float offset_x) { return ImGui::SetColumnOffset(column_index, offset_x); }, LUA_ARGS(int, float));
            module.addFunction(XorStringA("GetColumnWidth"), [](int column_index) { return ImGui::GetColumnWidth(column_index); }, LUA_ARGS(_def<int, -1>));
            module.addFunction(XorStringA("GetColumnsCount"), &ImGui::GetColumnsCount);
            module.addFunction(XorStringA("GetCursorPos"), &ImGui::GetCursorPos);
            module.addFunction(XorStringA("GetCursorPosX"), &ImGui::GetCursorPosX);
            module.addFunction(XorStringA("GetCursorPosY"), &ImGui::GetCursorPosY);
            module.addFunction(XorStringA("SetCursorPos"), [](ImVec2 pos) { return ImGui::SetCursorPos(pos); }, LUA_ARGS(ImVec2));
            module.addFunction(XorStringA("SetCursorPosX"), &ImGui::SetCursorPosX);
            module.addFunction(XorStringA("SetCursorPosY"), &ImGui::SetCursorPosY);
            module.addFunction(XorStringA("GetCursorStartPos"), &ImGui::GetScrollX);
            module.addFunction(XorStringA("GetCursorScreenPos"), &ImGui::GetScrollX);
            module.addFunction(XorStringA("SetCursorScreenPos"), [](ImVec2 pos) { return ImGui::SetCursorScreenPos(pos); }, LUA_ARGS(ImVec2));
            module.addFunction(XorStringA("AlignFirstTextHeightToWidgets"), &ImGui::AlignFirstTextHeightToWidgets);
            module.addFunction(XorStringA("GetTextLineHeight"), &ImGui::GetTextLineHeight);
            module.addFunction(XorStringA("GetTextLineHeightWithSpacing"), &ImGui::GetTextLineHeightWithSpacing);
            module.addFunction(XorStringA("GetItemsLineHeightWithSpacing"), &ImGui::GetItemsLineHeightWithSpacing);

            /*
            ID scopes
            */

            module.addFunction(XorStringA("PushID"), [](std::string id) { return ImGui::PushID(id.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("PushID"), [](std::string id_begin, std::string id_end) { return ImGui::PushID(id_begin.c_str(), id_end.c_str()); }, LUA_ARGS(std::string, std::string));
            module.addFunction(XorStringA("PushID"), [](int id) { return ImGui::PushID(id); }, LUA_ARGS(int));
            module.addFunction(XorStringA("PopID"), &ImGui::PopID);
            module.addFunction(XorStringA("GetID"), [](std::string id) { return ImGui::GetID(id.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("GetID"), [](std::string id_begin, std::string id_end) { return ImGui::GetID(id_begin.c_str(), id_end.c_str()); }, LUA_ARGS(std::string, std::string));

            /*
            Widgets
            */

            module.addFunction(XorStringA("Text"), [](std::string text) { return ImGui::Text(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("TextColored"), [](ImVec4 color, std::string text) { return ImGui::TextColored(color, text.c_str()); }, LUA_ARGS(ImVec4, std::string));
            module.addFunction(XorStringA("TextDisabled"), [](std::string text) { return ImGui::TextDisabled(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("TextWrapped"), [](std::string text) { return ImGui::TextWrapped(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("TextUnformatted"), [](std::string text, std::string text_end) { return ImGui::TextUnformatted(text.c_str(), text_end.c_str()); }, LUA_ARGS(std::string, _opt<std::string>));
            module.addFunction(XorStringA("Bullet"), &ImGui::Bullet);
            module.addFunction(XorStringA("BulletText"), [](std::string text) { return ImGui::BulletText(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("Button"), [](std::string label, ImVec2 size) { return ImGui::Button(label.c_str(), size); }, LUA_ARGS(std::string, _opt<ImVec2>));
            module.addFunction(XorStringA("SmallButton"), [](std::string text) { return ImGui::SmallButton(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("InvisibleButton"), [](std::string str_id, ImVec2 size) { return ImGui::InvisibleButton(str_id.c_str(), size); }, LUA_ARGS(std::string, ImVec2));
            // TODO : Image
            // TODO : ImageButton
            module.addFunction(XorStringA("CollapsingHeader"), [](std::string label, std::string str_id, bool display_frame, bool default_open) { return ImGui::CollapsingHeader(label.c_str(), str_id.c_str(), display_frame, default_open); }, LUA_ARGS(std::string, _opt<std::string>, _def<bool, true>, _def<bool, false>));
            module.addFunction(XorStringA("Checkbox"), [](std::string label, bool& v) { return ImGui::Checkbox(label.c_str(), (bool*)&v); }, LUA_ARGS(std::string, _ref<bool&>));
            module.addFunction(XorStringA("RadioButton"), [](std::string label, bool active) { return ImGui::RadioButton(label.c_str(), active); }, LUA_ARGS(std::string, bool));
            module.addFunction(XorStringA("Combo"), [](std::string label, int& current_item, std::vector<std::string> items, int height_in_items)
            {
                int item = current_item - 1;
                auto getter = [](void* data, int idx, const char** out_text) -> bool
                {
                    *out_text = static_cast<std::vector<std::string>*>(data)->at(idx).c_str();
                    return *out_text != nullptr;
                };
                if (ImGui::Combo(label.c_str(), &item, getter, (void*)&items, (int)items.size(), height_in_items))
                {
                    current_item = item + 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }, LUA_ARGS(std::string, _ref<int&>, std::vector<std::string>, _def<int, -1>));
            module.addFunction(XorStringA("ColorButton"), [](ImVec4 col, bool small_height, bool outline_border) { return ImGui::ColorButton(col, small_height, outline_border); }, LUA_ARGS(ImVec4, _def<bool, false>, _def<bool, true>));
            module.addFunction(XorStringA("ColorEdit3"), [](std::string label, std::vector<float>& items)
            {
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::ColorEdit3(label.c_str(), v);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>));
            module.addFunction(XorStringA("ColorEdit4"), [](std::string label, std::vector<float>& items, bool show_alpha)
            {
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::ColorEdit4(label.c_str(), v, show_alpha);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<bool, true>));
            module.addFunction(XorStringA("ColorEditMode"), &ImGui::ColorEditMode);
            // TODO : PlotLines
            // TODO : PlotHistogram

            /*
            Widgets: Drags
            */

            module.addFunction(XorStringA("DragFloat"), [](std::string label, float& v, float v_speed, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::DragFloat(label.c_str(), (float*)&v, v_speed, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("DragFloat2"), [](std::string label, std::vector<float>& items, float v_speed, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::DragFloat2(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("DragFloat3"), [](std::string label, std::vector<float>& items, float v_speed, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::DragFloat3(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("DragFloat4"), [](std::string label, std::vector<float>& items, float v_speed, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::DragFloat4(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("DragFloatRange2"), [](std::string label, float& v_current_min, float& v_current_max, float v_speed, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::DragFloatRange2(label.c_str(), (float*)&v_current_min, (float*)&v_current_max, v_speed, v_min, v_max, display_format.c_str(), display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, _ref<float&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("DragInt"), [](std::string label, int& v, float v_speed, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::DragInt(label.c_str(), (int*)&v, v_speed, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            module.addFunction(XorStringA("DragInt2"), [](std::string label, std::vector<int>& items, float v_speed, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::DragInt2(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            module.addFunction(XorStringA("DragInt3"), [](std::string label, std::vector<int>& items, float v_speed, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::DragInt3(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            module.addFunction(XorStringA("DragInt4"), [](std::string label, std::vector<int>& items, float v_speed, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::DragInt4(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            module.addFunction(XorStringA("DragIntRange2"), [](std::string label, int& v_current_min, int& v_current_max, float v_speed, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::DragIntRange2(label.c_str(), (int*)&v_current_min, (int*)&v_current_max, v_speed, v_min, v_max, display_format.c_str(), display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, _ref<int&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));

            /*
            Widgets: Input
            */

            module.addFunction(XorStringA("InputText"), [](std::string label, std::string& text, int max_size, int flags)
            {
                char *buffer = new char[max_size]();
                text.copy(buffer, text.size() < max_size ? text.size() : max_size);
                bool ret = ImGui::InputText(label.c_str(), buffer, max_size, flags);
                text = buffer;
                delete[] buffer;
                return ret;
            }, LUA_ARGS(std::string, _ref<std::string&>, _def<int, 255>, _def<int, 0>));
            module.addFunction(XorStringA("InputTextMultiline"), [](std::string label, std::string& text, int max_size, ImVec2 size, int flags)
            {
                char *buffer = new char[max_size]();
                text.copy(buffer, text.size() < max_size ? text.size() : max_size);
                bool ret = ImGui::InputTextMultiline(label.c_str(), buffer, max_size, size, flags);
                text = buffer;
                delete[] buffer;
                return ret;
            }, LUA_ARGS(std::string, _ref<std::string&>, _def<int, 255>, _opt<ImVec2>, _def<int, 0>));
            module.addFunction(XorStringA("InputFloat"), [](std::string label, float& v, float step, float step_fast, int decimal_precision, int extra_flags)
            {
                return ImGui::InputFloat(label.c_str(), (float*)&v, step, step_fast, decimal_precision, extra_flags);
            }, LUA_ARGS(std::string, _ref<float&>, _def_float(0.0f), _def_float(0.0f), _def<int, -1>, _def<int, 0>));
            module.addFunction(XorStringA("InputFloat2"), [](std::string label, std::vector<float>& items, int decimal_precision, int extra_flags)
            {
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::InputFloat2(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            module.addFunction(XorStringA("InputFloat3"), [](std::string label, std::vector<float>& items, int decimal_precision, int extra_flags)
            {
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::InputFloat3(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            module.addFunction(XorStringA("InputFloat4"), [](std::string label, std::vector<float>& items, int decimal_precision, int extra_flags)
            {
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::InputFloat4(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            module.addFunction(XorStringA("InputInt"), [](std::string label, int& v, int step, int step_fast, int extra_flags)
            {
                return ImGui::InputInt(label.c_str(), (int*)&v, step, step_fast, extra_flags);
            }, LUA_ARGS(std::string, _ref<int&>, _def<int, 1>, _def<int, 100>, _def<int, 0>));
            module.addFunction(XorStringA("InputInt2"), [](std::string label, std::vector<int>& items, int extra_flags)
            {
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::InputInt2(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));
            module.addFunction(XorStringA("InputInt3"), [](std::string label, std::vector<int>& items, int extra_flags)
            {
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::InputInt3(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));
            module.addFunction(XorStringA("InputInt4"), [](std::string label, std::vector<int>& items, int extra_flags)
            {
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::InputInt4(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));


            /*
            Widgets: Sliders
            */

            module.addFunction(XorStringA("SliderFloat"), [](std::string label, float& v, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::SliderFloat(label.c_str(), (float*)&v, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, float, float, _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("SliderFloat2"), [](std::string label, std::vector<float>& items, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::SliderFloat2(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("SliderFloat3"), [](std::string label, std::vector<float>& items, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::SliderFloat3(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("SliderFloat4"), [](std::string label, std::vector<float>& items, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::SliderFloat4(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("SliderInt"), [](std::string label, int& v, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::SliderInt(label.c_str(), (int*)&v, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, int, int, _opt<std::string>));
            module.addFunction(XorStringA("SliderInt2"), [](std::string label, std::vector<int>& items, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::SliderInt2(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            module.addFunction(XorStringA("SliderInt3"), [](std::string label, std::vector<int>& items, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::SliderInt3(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            module.addFunction(XorStringA("SliderInt4"), [](std::string label, std::vector<int>& items, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::SliderInt4(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            module.addFunction(XorStringA("VSliderFloat"), [](std::string label, ImVec2 size, float& v, float v_min, float v_max, std::string display_format, float power)
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::VSliderFloat(label.c_str(), size, (float*)&v, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, ImVec2, _ref<float&>, float, float, _opt<std::string>, _def_float(1.0f)));
            module.addFunction(XorStringA("VSliderInt"), [](std::string label, ImVec2 size, int& v, int v_min, int v_max, std::string display_format)
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::VSliderInt(label.c_str(), size, (int*)&v, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, ImVec2, _ref<int&>, int, int, _opt<std::string>));

            /*
            Widgets: Trees
            */

            module.addFunction(XorStringA("TreeNode"), [](std::string label) { return ImGui::TreeNode(label.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("TreePush"), [](std::string id) { return ImGui::TreePush(id.c_str()); }, LUA_ARGS(_opt<std::string>));
            module.addFunction(XorStringA("TreePop"), &ImGui::TreePop);
            module.addFunction(XorStringA("SetNextTreeNodeOpened"), [](bool opened, int cond) { return ImGui::SetNextTreeNodeOpened(opened, cond); }, LUA_ARGS(bool, _def<int, 0>));

            /*
            Widgets: Selectable / List
            */

            module.addFunction(XorStringA("Selectable"), [](std::string label, bool& selected, int flags, ImVec2 size) { return ImGui::Selectable(label.c_str(), (bool*)&selected, flags, size); }, LUA_ARGS(std::string, _ref<bool&>, int, ImVec2));
            module.addFunction(XorStringA("ListBox"), [](std::string label, int& current_item, std::vector<std::string> items, int height_in_items)
            {
                int item = current_item - 1;
                auto getter = [](void* data, int idx, const char** out_text) -> bool {  *out_text = static_cast<std::vector<std::string>*>(data)->at(idx).c_str(); return *out_text != nullptr; };
                if (ImGui::ListBox(label.c_str(), &item, getter, (void*)&items, (int)items.size(), height_in_items))
                {
                    current_item = item + 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }, LUA_ARGS(std::string, _ref<int&>, std::vector<std::string>, _def<int, -1>));
            module.addFunction(XorStringA("ListBoxHeader"), [](std::string label, ImVec2 size) { return ImGui::ListBoxHeader(label.c_str(), size); }, LUA_ARGS(std::string, ImVec2));
            module.addFunction(XorStringA("ListBoxHeader"), [](std::string label, int items_count, int height_in_items) { return ImGui::ListBoxHeader(label.c_str(), items_count, height_in_items); }, LUA_ARGS(std::string, int, _def<int, -1>));
            module.addFunction(XorStringA("ListBoxFooter"), &ImGui::ListBoxFooter);

            /*
            TODO : Widgets: Value()
            */

            /*
            Tooltip
            */

            module.addFunction(XorStringA("SetTooltip"), [](std::string text) { return ImGui::SetTooltip(text.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("BeginTooltip"), &ImGui::BeginTooltip);
            module.addFunction(XorStringA("EndTooltip"), &ImGui::EndTooltip);

            /*
            Menus
            */
            module.addFunction(XorStringA("BeginMainMenuBar"), &ImGui::BeginMainMenuBar);
            module.addFunction(XorStringA("EndMainMenuBar"), &ImGui::EndMainMenuBar);
            module.addFunction(XorStringA("BeginMenuBar"), &ImGui::BeginMenuBar);
            module.addFunction(XorStringA("EndMenuBar"), &ImGui::EndMenuBar);
            module.addFunction(XorStringA("BeginMenu"), [](std::string text, bool enabled) { return ImGui::BeginMenu(text.c_str(), enabled); }, LUA_ARGS(std::string, _def<bool, true>));
            module.addFunction(XorStringA("EndMenu"), &ImGui::EndMenu);
            module.addFunction(XorStringA("MenuItem"), [](std::string text, std::string shortcut, bool& selected, bool enabled) { return ImGui::MenuItem(text.c_str(), shortcut.c_str(), (bool*)&selected, enabled); }, LUA_ARGS(std::string, std::string, _ref<bool&>, _def<bool, true>));

            /*
            Popup
            */

            module.addFunction(XorStringA("OpenPopup"), [](std::string id) { return ImGui::OpenPopup(id.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("BeginPopup"), [](std::string id) { return ImGui::BeginPopup(id.c_str()); }, LUA_ARGS(std::string));
            module.addFunction(XorStringA("BeginPopupModal"), [](std::string name, bool& opened, int extra_flags) { return ImGui::BeginPopupModal(name.c_str(), (bool*)&opened, extra_flags); }, LUA_ARGS(std::string, _ref<bool&>, _def<int, 0>));
            module.addFunction(XorStringA("BeginPopupContextItem"), [](std::string id, int mouse_button) { return ImGui::BeginPopupContextItem(id.c_str(), mouse_button); }, LUA_ARGS(std::string, _def<int, 1>));
            module.addFunction(XorStringA("BeginPopupContextWindow"), [](bool also_over_item, std::string id, int mouse_button) { return ImGui::BeginPopupContextWindow(also_over_item, id.c_str(), mouse_button); }, LUA_ARGS(_def<bool, true>, _opt<std::string>, _def<int, 1>));
            module.addFunction(XorStringA("BeginPopupContextVoid"), [](std::string id, int mouse_button) { return ImGui::BeginPopupContextVoid(id.c_str(), mouse_button); }, LUA_ARGS(_opt<std::string>, _def<int, 1>));
            module.addFunction(XorStringA("EndPopup"), &ImGui::EndPopup);
            module.addFunction(XorStringA("CloseCurrentPopup"), &ImGui::CloseCurrentPopup);


            /*
            TODO : Utilities
            */

            /*
            TODO : Inputs
            */

            module.endModule();

        }

    }
}
