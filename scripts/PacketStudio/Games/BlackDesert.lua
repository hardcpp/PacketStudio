-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

function PacketStudio_Game_BlackDesert_Setup()
    print("Initializing BlackDesert")

    PacketStudio.PacketTypes = BlackDesertOpcodes;

    Parsers.Folder = "BlackDesert"
    Parsers.Init()
end