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

            // TODO : GetWindowDrawList
            // TODO : GetWindowFont


            // TODO : SetStateStorage
            // TODO : GetStateStorage

            /*
            TODO : Parameters stacks (shared)
            */

            /*
            TODO : Parameters stacks (current window)
            */

            /*
            Cursor / Layout
            */



            /*
            ID scopes
            */


            /*
            Widgets
            */

            // TODO : Image
            // TODO : ImageButton
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
            {
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::ColorEdit3(label.c_str(), v);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>));
            {
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::ColorEdit4(label.c_str(), v, show_alpha);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<bool, true>));
            // TODO : PlotLines
            // TODO : PlotHistogram

            /*
            Widgets: Drags
            */

            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::DragFloat(label.c_str(), (float*)&v, v_speed, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::DragFloat2(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::DragFloat3(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::DragFloat4(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::DragFloatRange2(label.c_str(), (float*)&v_current_min, (float*)&v_current_max, v_speed, v_min, v_max, display_format.c_str(), display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, _ref<float&>, _def_float(1.0f), _def_float(0.0f), _def_float(0.0), _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::DragInt(label.c_str(), (int*)&v, v_speed, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::DragInt2(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::DragInt3(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::DragInt4(label.c_str(), v, v_speed, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::DragIntRange2(label.c_str(), (int*)&v_current_min, (int*)&v_current_max, v_speed, v_min, v_max, display_format.c_str(), display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, _ref<int&>, _def_float(1.0f), _def<int, 0>, _def<int, 0>, _opt<std::string>));

            /*
            Widgets: Input
            */

            {
                char *buffer = new char[max_size]();
                text.copy(buffer, text.size() < max_size ? text.size() : max_size);
                bool ret = ImGui::InputText(label.c_str(), buffer, max_size, flags);
                text = buffer;
                delete[] buffer;
                return ret;
            }, LUA_ARGS(std::string, _ref<std::string&>, _def<int, 255>, _def<int, 0>));
            {
                char *buffer = new char[max_size]();
                text.copy(buffer, text.size() < max_size ? text.size() : max_size);
                bool ret = ImGui::InputTextMultiline(label.c_str(), buffer, max_size, size, flags);
                text = buffer;
                delete[] buffer;
                return ret;
            }, LUA_ARGS(std::string, _ref<std::string&>, _def<int, 255>, _opt<ImVec2>, _def<int, 0>));
            {
                return ImGui::InputFloat(label.c_str(), (float*)&v, step, step_fast, decimal_precision, extra_flags);
            }, LUA_ARGS(std::string, _ref<float&>, _def_float(0.0f), _def_float(0.0f), _def<int, -1>, _def<int, 0>));
            {
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::InputFloat2(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            {
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::InputFloat3(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            {
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::InputFloat4(label.c_str(), v, decimal_precision, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, _def<int, -1>, _def<int, 0>));
            {
                return ImGui::InputInt(label.c_str(), (int*)&v, step, step_fast, extra_flags);
            }, LUA_ARGS(std::string, _ref<int&>, _def<int, 1>, _def<int, 100>, _def<int, 0>));
            {
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::InputInt2(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));
            {
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::InputInt3(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));
            {
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::InputInt4(label.c_str(), v, extra_flags);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, _def<int, 0>));


            /*
            Widgets: Sliders
            */

            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::SliderFloat(label.c_str(), (float*)&v, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, _ref<float&>, float, float, _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::SliderFloat2(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::SliderFloat3(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.3f";
                float v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::SliderFloat4(label.c_str(), v, v_min, v_max, display_format.c_str(), power);
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<float>&>, float, float, _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::SliderInt(label.c_str(), (int*)&v, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, _ref<int&>, int, int, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1) };
                bool ret = ImGui::SliderInt2(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2) };
                bool ret = ImGui::SliderInt3(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.0f";
                int v[] = { items.at(0), items.at(1), items.at(2), items.at(3) };
                bool ret = ImGui::SliderInt4(label.c_str(), v, v_min, v_max, display_format.c_str());
                for (int i = 0; i < items.size(); i++) items[i] = v[i];
                return ret;
            }, LUA_ARGS(std::string, _ref<std::vector<int>&>, int, int, _opt<std::string>));
            {
                if (display_format.empty()) display_format = "%.3f";
                return ImGui::VSliderFloat(label.c_str(), size, (float*)&v, v_min, v_max, display_format.c_str(), power);
            }, LUA_ARGS(std::string, ImVec2, _ref<float&>, float, float, _opt<std::string>, _def_float(1.0f)));
            {
                if (display_format.empty()) display_format = "%.0f";
                return ImGui::VSliderInt(label.c_str(), size, (int*)&v, v_min, v_max, display_format.c_str());
            }, LUA_ARGS(std::string, ImVec2, _ref<int&>, int, int, _opt<std::string>));

            /*
            Widgets: Trees
            */


            /*
            Widgets: Selectable / List
            */

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

            /*
            TODO : Widgets: Value()
            */

            /*
            Tooltip
            */


            /*
            Menus
            */

            /*
            Popup
            */



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
