-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

BlackDesertOpcodes = {}

BlackDesertOpcodes[0x03E9] = { 0x03E9, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_HEARTBEAT" }
BlackDesertOpcodes[0x03EB] = { 0x03EB, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_SET_FRAMEWORK_INFORMATION" }
BlackDesertOpcodes[0x03F0] = { 0x03F0, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_AUTHENTICATE_TO_PARENT_SERVER" }
BlackDesertOpcodes[0x03F3] = { 0x03F3, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_NAK" }
BlackDesertOpcodes[0x079F] = { 0x079F, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_HANDLE_SERVER_SESSION_ESTABLISH" }
BlackDesertOpcodes[0x07A0] = { 0x07A0, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_HANDLE_CLIENT_SESSION_ESTABLISH" }
BlackDesertOpcodes[0x07A1] = { 0x07A1, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_HANDLE_SERVER_SESSION_DISCONNECT_COMPLETE" }
BlackDesertOpcodes[0x07A2] = { 0x07A2, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_HANDLE_CLIENT_SESSION_DISCONNECT_COMPLETE" }
BlackDesertOpcodes[0x07A7] = { 0x07A7, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_CHECK_ALL_PC_HEARTBEAT" }
BlackDesertOpcodes[0x07D1] = { 0x07D1, GlobalEnums.PacketDirection.CLIENT_TO_SERVER, "CMSG_STOP_SERVICE" }
BlackDesertOpcodes[0x0BB9] = { 0x0BB9, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_PLAYERSS" }
BlackDesertOpcodes[0x0BBA] = { 0x0BBA, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_MONSTERSS" }
BlackDesertOpcodes[0x0BBB] = { 0x0BBB, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_NPCSS" }
BlackDesertOpcodes[0x0BBC] = { 0x0BBC, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_DEAD_BODYSS" }
BlackDesertOpcodes[0x0BBD] = { 0x0BBD, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_GRAVESS" }
BlackDesertOpcodes[0x0BBE] = { 0x0BBE, GlobalEnums.PacketDirection.SERVER_TO_CLIENT, "SMSG_ADD_VEHICLESS" }
