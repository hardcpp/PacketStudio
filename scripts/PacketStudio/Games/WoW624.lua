-- Packet studio
-- Copryright hardcpp@gmail.com

function PacketStudio_Game_BlackDesert_Setup()
    print("Initializing WoW624")

    PacketStudio.PacketTypes = WoW624Opcodes;

    Parsers.Folder = "WoW624"
    Parsers.Init()
end