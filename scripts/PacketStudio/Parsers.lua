-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

Parsers = {}
Parsers.ListCache = {}
Parsers.Folder = ""

Parsers.NodeTypes = {
    Var = 1,
    Block = 2,
    Loop = 3
}

Parsers.FieldTypes = {
    Uint8 = 1,
    Int8 = 2,
    Uint16 = 3,
    Int16 = 4,
    Uint32 = 5,
    Int32 = 6,
    Uint64 = 7,
    Int64 = 8,
    Float = 9,
    Double = 10,
    String = 11
}
Parsers.FieldTypesName = {
    "Uint8",
    "Int8",
    "Uint16",
    "Int16",
    "Uint32",
    "Int32",
    "Uint64",
    "Int64",
    "Float",
    "Double",
    "String"
}
-- Struct :
-- 1 => Type
-- 2 => Name
-- 3 => CacheID
-- Var
--     4 - Type
--     5 - EnumName
-- Block
--     4 - Childs
-- Loop
--     4 - Counter
--     5 - Childs
-- =======================================================
-- Methods
-- =======================================================

-- Reset cache ID before saving
-- @p_Node : Current node to reset
function Parsers.ResetCacheID(p_Node)
    for l_Key,l_Value in pairs(p_Node) do
        local l_NodeType    = l_Value[1]
        l_Value[3] = "null_cache_id"

        if l_NodeType == Parsers.NodeTypes.Block then
            Parsers.ResetCacheID(l_Value[4])
        elseif l_NodeType == Parsers.NodeTypes.Loop then
            Parsers.ResetCacheID(l_Value[5])
        end
    end

    return p_Node
end

-- Init parsers, this method will read all parsers present in the gamefolder
function Parsers.Init()
    local l_Path = "PacketStudio\\" .. Parsers.Folder .. "\\Parsers\\"
    for l_Key,l_Value in pairs(PacketStudio.PacketTypes) do
        local l_File = io.open(l_Path .. l_Value[3] .. ".psp", "r")

        if l_File~=nil then
            Parsers.ParserArray[l_Key] = Helpers.TableUnserialize(l_File:read("*all"))
            io.close(l_File)
        else
            Parsers.ParserArray[l_Key] = nil;
        end
    end
end

-- Create a new parser
-- @p_Value : Packet type
-- @p_Name  : Packet name
function Parsers.Create(p_Value, p_Name)
    os.execute("mkdir " .. "PacketStudio");
    os.execute("mkdir " .. "PacketStudio\\" .. Parsers.Folder);
    os.execute("mkdir " .. "PacketStudio\\" .. Parsers.Folder .. "\\Parsers");

    local l_Path = "PacketStudio\\" .. Parsers.Folder .. "\\Parsers\\" .. p_Name .. ".psp"

    local l_File = io.open(l_Path, "w+")
    l_File:write(Helpers.TableSerialize( {} ))
    l_File:close()

    Parsers.ParserArray[p_Value] = { };
end

-- Delete a packet parser
-- @p_Value : Packet type
-- @p_Name  : Packet name
function Parsers.Delete(p_Value, p_Name)
    local l_Path = "PacketStudio\\" .. Parsers.Folder .. "\\Parsers\\" .. p_Name .. ".psp"
    os.remove(l_Path)

    Parsers.ParserArray[p_Value] = nil;
end

-- Save a packet parser
-- @p_Value : Packet type
function Parsers.Save(p_Value)
    local l_Path = "PacketStudio\\" .. Parsers.Folder .. "\\Parsers\\" .. PacketStudio.PacketTypes[p_Value][3] .. ".psp"

    local l_File = io.open(l_Path, "w+")
    l_File:write(Helpers.TableSerialize(Parsers.ResetCacheID(Parsers.ParserArray[p_Value])))
    l_File:close()
end