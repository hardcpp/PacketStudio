-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

PacketStudio.Views.Enums = {}
PacketStudio.Views.Enums.Visible = false

local g_PacketTypeFilter = ""

-- =======================================================
-- Render function
-- =======================================================
function PacketStudio_Enums_MainDraw()
    if PacketStudio.Views.Enums.Visible == false then
        return
    end

    local l_MainWindow;
    _, l_MainWindow = ImGui.Begin("PacketStudio::Enums", true, ImVec2(600, 400), -1.0)
    if l_MainWindow then
        ImGui.Text("Enums Filter :")
        ImGui.SameLine();
        _, g_PacketTypeFilter = ImGui.InputText("", g_PacketTypeFilter)
        ImGui.Separator()

        if ImGui.CollapsingHeader("Results", "id_enums_result", true) then
            ImGui.Columns(3, "packet_types")
            ImGui.SetColumnOffset(1, 100)
            ImGui.SetColumnOffset(2, 300)
            ImGui.SetColumnOffset(3, 800)
            for l_Key,l_Value in pairs(PacketStudio.PacketTypes) do
                local l_OpcodeHex 		= "0x" .. Helpers.NumToHex(l_Value[1], 4)
                local l_DirectionStr 	= "SERVER_TO_CLIENT"

                if l_Value[2] == GlobalEnums.PacketDirection.CLIENT_TO_SERVER then
                    l_DirectionStr = "SERVER_TO_CLIENT"
                end

                if g_PacketTypeFilter:len() ~= 0 then
                    local l_MatchA = string.find(l_OpcodeHex, g_PacketTypeFilter:lower()) and true or false

                    if not l_MatchA then
                        goto enums_continue
                    end
                end

                ImGui.Text(l_OpcodeHex)
                ImGui.NextColumn()
                ImGui.Text(l_DirectionStr)
                ImGui.NextColumn()
                ImGui.Text(tostring(l_Value[3]))
                ImGui.NextColumn()

                ::enums_continue::
            end
            ImGui.Columns(1)
        end

        ImGui.End()
    else
        PacketStudio.Views.Enums.Visible = false
    end
end

-- =======================================================
-- Callbacks registration
-- =======================================================

Pyx.Scripting.CurrentScript:RegisterCallback("ImGui.OnRender", PacketStudio_Enums_MainDraw)