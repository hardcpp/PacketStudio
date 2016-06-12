-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

PacketStudio.CurrentGame = "#NONE";
PacketStudio.IsInit = false;

-- =======================================================
-- Game selection
-- =======================================================
function PacketStudio_DrawGameSelection()
    if ImGui.CollapsingHeader("Game selection", "id_game_selection", true) then
        ImGui.Text("Current : " .. PacketStudio.CurrentGame)
        ImGui.Separator()

        -- Enumerate game
        for l_Key,l_Value in pairs(GlobalEnums.Game) do
            if ImGui.Button(tostring(l_Value[1]), ImVec2(180, 20)) then
                l_Value[2]();
                PacketStudio.CurrentGame = l_Value[1];
                PacketStudio.IsInit = true;
            end
        end
    end
end

-- =======================================================
-- View selection
-- =======================================================
function PacketStudio_DrawViewSelection()
    if ImGui.CollapsingHeader("Views", "id_view_selection") then
        if ImGui.Button("Packet Parser editor", ImVec2(180, 20)) then
            if PacketStudio.IsInit == true then
                PacketStudio.Views.PacketParserEditor.Visible = true;
            else
                -- @TODO Show error ?
            end
        end
        if ImGui.Button("Packet types", ImVec2(180, 20)) then
            if PacketStudio.IsInit == true then
                PacketStudio.Views.PacketTypes.Visible = true;
            else
                -- @TODO Show error ?
            end
        end
    end
end

-- =======================================================
-- Render function
-- =======================================================
function PacketStudio_MainDraw()
    local l_MainWindow;
    _, l_MainWindow = ImGui.Begin("PacketStudio::Main e", true, ImVec2(200, 400), -1.0)
    if l_MainWindow then
        PacketStudio_DrawGameSelection();
        PacketStudio_DrawViewSelection();

        ImGui.End()
    end
end

-- =======================================================
-- Callbacks registration
-- =======================================================

Pyx.Scripting.CurrentScript:RegisterCallback("ImGui.OnRender", PacketStudio_MainDraw)