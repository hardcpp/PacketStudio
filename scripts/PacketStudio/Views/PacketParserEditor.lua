-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

PacketStudio.Views.PacketParserEditor = {}
PacketStudio.Views.PacketParserEditor.Visible = false
PacketStudio.Views.PacketParserEditor.ActivePacket = -1
PacketStudio.Views.PacketParserEditor.CurrentReaderTable = {}

local g_PacketTypeFilter = ""

-- =======================================================
-- Render function
-- =======================================================
function PacketStudio_PacketParserEditor_DrawPacketSelector()
    ImGui.Text("Filter :")
    ImGui.SameLine();
    _, g_PacketTypeFilter = ImGui.InputText("", g_PacketTypeFilter)
    ImGui.Separator()

    -- Packet list
    if ImGui.CollapsingHeader("Results", "id_packet_parser_editor_packet_result", true) then
        ImGui.Columns(3, "id_packet_parser_editor_packet")
        ImGui.SetColumnOffset(1, 100)
        ImGui.SetColumnOffset(2, 500)
        ImGui.SetColumnOffset(3, 900)

        for l_Key,l_Value in pairs(PacketStudio.PacketTypes) do
            local l_OpcodeHex = "0x" .. Helpers.NumToHex(l_Key, 4)

            if g_PacketTypeFilter:len() ~= 0 then
                local l_MatchA = string.find(l_OpcodeHex, g_PacketTypeFilter:lower()) and true or false
                local l_MatchB = string.find(l_Value[3]:lower(), g_PacketTypeFilter:lower()) and true or false

                if not l_MatchA and not l_MatchB then
                    goto packet_types_continue
                end
            end

            ImGui.Text(l_OpcodeHex)
            ImGui.NextColumn()
            ImGui.Text(l_Value[3])
            ImGui.NextColumn()

            local l_HaveParser = false

            if Parsers.ParserArray[l_Key] ~= nil then
                l_HaveParser = true
            end

            if l_HaveParser then
                if ImGui.Button("View##packet_parser_editor_" .. l_Key) then
                    PacketStudio.Views.PacketParserEditor.ActivePacket          = l_Key
                    PacketStudio.Views.PacketParserEditor.CurrentReaderTable    = Helpers.TableCopy(Parsers.ParserArray[l_Key])
                end
                ImGui.SameLine()
                if ImGui.Button("Delete##packet_parser_editor_" .. l_Key) then
                    Parsers.Delete(l_Key, l_Value[3])
                end
            else
                if ImGui.Button("Create##packet_parser_editor_" .. l_Key) then
                    Parsers.Create(l_Key, l_Value[3])
                    PacketStudio.Views.PacketParserEditor.ActivePacket          = l_Key
                    PacketStudio.Views.PacketParserEditor.CurrentReaderTable    = Helpers.TableCopy(Parsers.ParserArray[l_Key])
                end
                ImGui.SameLine()
                if ImGui.Button("Recheck##packet_parser_editor_" .. l_Key) then

                end
            end

            ImGui.NextColumn()

            ::packet_types_continue::
        end

        ImGui.Columns(1)
    end
end

local l_GUIIDGENERATOR = 1
function PacketStudio_PacketParserEditor_DrawPacketReader_HandleNode(p_Node, p_GlobalNames)
    if p_Node ~= nil or #p_Node > 0 then
        ImGui.Indent(10)

        for l_Key,l_Value in pairs(p_Node) do
            local l_NodeType    = l_Value[1]
            local l_Name        = tostring(l_Value[2])
            local l_CacheID     = l_Value[3]

            if l_CacheID == nil or l_CacheID == "null_cache_id" or l_CacheID == "" then
                l_GUIIDGENERATOR = l_GUIIDGENERATOR + 1
                l_CacheID = "##id_packet_parser_widget_" .. tostring(l_GUIIDGENERATOR) .. tostring(PacketStudio.Views.PacketParserEditor.ActivePacket)
                p_Node[l_Key][3] = l_CacheID
            end

            if l_NodeType == Parsers.NodeTypes.Var then
                ImGui.Text("|-")
                ImGui.SameLine()
                ImGui.TextColored(ImVec4(1,0,0,1), "FieldName :")
                ImGui.SameLine()
                ImGui.PushItemWidth(300)
                _, p_Node[l_Key][2] = ImGui.InputText(l_CacheID .. "name_edit", l_Name)
                ImGui.PopItemWidth()
                ImGui.SameLine()

                ImGui.PushItemWidth(150)
                _, p_Node[l_Key][4] = ImGui.Combo(l_CacheID .. "_type_combo", p_Node[l_Key][4], Parsers.FieldTypesName, #Parsers.FieldTypesName)
                ImGui.PopItemWidth()

                ImGui.SameLine()
                if ImGui.Button("Up##" .. l_CacheID .. "_up") and l_Key > 1 then
                    local l_Prev    = p_Node[l_Key - 1];
                    local l_Current = p_Node[l_Key];

                    p_Node[l_Key - 1]   = l_Current
                    p_Node[l_Key]       = l_Prev

                    goto handle_node_end
                end
                ImGui.SameLine()
                if ImGui.Button("Down##" .. l_CacheID .. "_down") and l_Key < #p_Node then
                    local l_Current = p_Node[l_Key];
                    local l_Next    = p_Node[l_Key + 1];

                    p_Node[l_Key + 1]   = l_Current
                    p_Node[l_Key]       = l_Next

                    goto handle_node_end
                end
                ImGui.SameLine()
                if ImGui.Button("Del##" .. l_CacheID .. "_del") then
                    p_Node[l_Key] = nil;
                end

            elseif l_NodeType == Parsers.NodeTypes.Block then

                if ImGui.CollapsingHeader("BLOCK => " .. l_Name, l_CacheID) then
                    ImGui.Text("|-")
                    ImGui.SameLine()
                    ImGui.TextColored(ImVec4(0,1,0,1), "BlockName :")
                    ImGui.SameLine()
                    ImGui.PushItemWidth(300)
                    _, p_Node[l_Key][2] = ImGui.InputText(l_CacheID .. "name_edit", l_Name)
                    ImGui.PopItemWidth()
                    ImGui.SameLine()
                    if ImGui.Button("Up##" .. l_CacheID .. "_up") and l_Key > 1 then
                        local l_Prev    = p_Node[l_Key - 1];
                        local l_Current = p_Node[l_Key];

                        p_Node[l_Key - 1]   = l_Current
                        p_Node[l_Key]       = l_Prev

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Down##" .. l_CacheID .. "_down") and l_Key < #p_Node then
                        local l_Current = p_Node[l_Key];
                        local l_Next    = p_Node[l_Key + 1];

                        p_Node[l_Key + 1]   = l_Current
                        p_Node[l_Key]       = l_Next

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Del##" .. l_CacheID .. "_del") then
                        p_Node[l_Key] = nil;
                    end
                    ImGui.Separator()
                    PacketStudio_PacketParserEditor_DrawPacketReader_HandleNode(l_Value[4], p_GlobalNames)

                end
                ImGui.Separator()

            elseif l_NodeType == Parsers.NodeTypes.Loop then

                if ImGui.CollapsingHeader("LOOP => " .. l_Name, l_CacheID) then
                    ImGui.Text("|-")
                    ImGui.SameLine()
                    ImGui.TextColored(ImVec4(0,1,0,1), "LoopName :")
                    ImGui.SameLine()
                    ImGui.PushItemWidth(300)
                    _, p_Node[l_Key][2] = ImGui.InputText(l_CacheID .. "name_edit", l_Name)
                    ImGui.PopItemWidth()
                    ImGui.SameLine()
                    if ImGui.Button("Up##" .. l_CacheID .. "_up") and l_Key > 1 then
                        local l_Prev    = p_Node[l_Key - 1];
                        local l_Current = p_Node[l_Key];

                        p_Node[l_Key - 1]   = l_Current
                        p_Node[l_Key]       = l_Prev

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Down##" .. l_CacheID .. "_down") and l_Key < #p_Node then
                        local l_Current = p_Node[l_Key];
                        local l_Next    = p_Node[l_Key + 1];

                        p_Node[l_Key + 1]   = l_Current
                        p_Node[l_Key]       = l_Next

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Del##" .. l_CacheID .. "_del") then
                        p_Node[l_Key] = nil;
                    end
                    ImGui.Separator()

                    PacketStudio_PacketParserEditor_DrawPacketReader_HandleNode(l_Value[5], p_GlobalNames)
                end

            elseif l_NodeType == Parsers.NodeTypes.GlobalParser then

                if ImGui.CollapsingHeader("GlobalParser => " .. l_Name, l_CacheID) then
                    ImGui.Text("|-")
                    ImGui.SameLine()
                    ImGui.TextColored(ImVec4(0,1,0,1), "GlobalParserName :")
                    ImGui.SameLine()
                    ImGui.PushItemWidth(300)
                    _, p_Node[l_Key][2] = ImGui.InputText(l_CacheID .. "name_edit", l_Name)
                    ImGui.PopItemWidth()
                    ImGui.SameLine()
                    ImGui.Text("|")
                    ImGui.SameLine()

                    local l_GlobalIndex = Parsers.FindGlobalByName(l_Value[4])

                    ImGui.PushItemWidth(150)
                    local l_NewGlobalIndex = 0
                    _, l_NewGlobalIndex = ImGui.Combo(l_CacheID .. "_parser_combo", l_GlobalIndex, p_GlobalNames, #p_GlobalNames)
                    ImGui.PopItemWidth()

                    if l_NewGlobalIndex ~= l_GlobalIndex then

                        p_Node[l_Key][4] = Parsers.GlobalParserArray[l_NewGlobalIndex][1]
                    end

                    ImGui.SameLine()
                    ImGui.Text("|")
                    ImGui.SameLine()

                    if ImGui.Button("Up##" .. l_CacheID .. "_up") and l_Key > 1 then
                        local l_Prev    = p_Node[l_Key - 1];
                        local l_Current = p_Node[l_Key];

                        p_Node[l_Key - 1]   = l_Current
                        p_Node[l_Key]       = l_Prev

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Down##" .. l_CacheID .. "_down") and l_Key < #p_Node then
                        local l_Current = p_Node[l_Key];
                        local l_Next    = p_Node[l_Key + 1];

                        p_Node[l_Key + 1]   = l_Current
                        p_Node[l_Key]       = l_Next

                        goto handle_node_end
                    end
                    ImGui.SameLine()
                    if ImGui.Button("Del##" .. l_CacheID .. "_del") then
                        p_Node[l_Key] = nil;
                    end
                    ImGui.Separator()

                end

            end
        end
    end

    if ImGui.Button("Add Var##packet_editor_addvar_" .. tostring(p_Node)) then
        p_Node[#p_Node + 1] = { Parsers.NodeTypes.Var, "Var", "null_cache_id", Parsers.FieldTypes.Int32 }
    end
    ImGui.SameLine()
    if ImGui.Button("Add Block##packet_editor_addblock_" .. tostring(p_Node)) then
        p_Node[#p_Node + 1] = { Parsers.NodeTypes.Block, "Block", "null_cache_id", { } }
    end
    ImGui.SameLine()
    if ImGui.Button("Add Loop##packet_editor_addloop_" .. tostring(p_Node)) then
        p_Node[#p_Node + 1] = { Parsers.NodeTypes.Loop, "Loop", "null_cache_id", "", { } }
    end
    ImGui.SameLine()
    if ImGui.Button("Add GlobalParser##packet_editor_addglobalparser_" .. tostring(p_Node)) then
        p_Node[#p_Node + 1] = { Parsers.NodeTypes.GlobalParser, "GlobalParser", "null_cache_id", "" }
    end

    ::handle_node_end::

    ImGui.Unindent(10)
end

function PacketStudio_PacketParserEditor_DrawPacketReader()
    if ImGui.Button("Save##packet_parser_editor") then
        Parsers.ParserArray[PacketStudio.Views.PacketParserEditor.ActivePacket] = Helpers.TableCopy(PacketStudio.Views.PacketParserEditor.CurrentReaderTable)
        Parsers.Save(PacketStudio.Views.PacketParserEditor.ActivePacket)
    end
    ImGui.SameLine()
    if ImGui.Button("Close##packet_parser_editor") then
        PacketStudio.Views.PacketParserEditor.ActivePacket = -1
    end
    ImGui.SameLine()
    if ImGui.Button("Reset##packet_parser_editor") then
        PacketStudio.Views.PacketParserEditor.CurrentReaderTable = Helpers.TableCopy(Parsers.ParserArray[PacketStudio.Views.PacketParserEditor.ActivePacket])
    end

    ImGui.Separator()
    ImGui.Separator()

    local l_GlobalParsersNameList = Parsers.GetGlobalNameList()

    PacketStudio_PacketParserEditor_DrawPacketReader_HandleNode(PacketStudio.Views.PacketParserEditor.CurrentReaderTable, l_GlobalParsersNameList);
end

function PacketStudio_PacketParserEditor_MainDraw()
    if PacketStudio.Views.PacketParserEditor.Visible == false then
        return
    end

    local l_MainWindow;
    _, l_MainWindow = ImGui.Begin("PacketStudio::PacketParserEditor", true, ImVec2(600, 400), -1.0)
    if l_MainWindow then

        if PacketStudio.Views.PacketParserEditor.ActivePacket == -1 then
            PacketStudio_PacketParserEditor_DrawPacketSelector()
        else
            PacketStudio_PacketParserEditor_DrawPacketReader()
        end

        ImGui.Separator()

        ImGui.End()
    else
        PacketStudio.Views.PacketParserEditor.Visible = false
    end
end

-- =======================================================
-- Callbacks registration
-- =======================================================

Pyx.Scripting.CurrentScript:RegisterCallback("ImGui.OnRender", PacketStudio_PacketParserEditor_MainDraw)