-- Packet studio
-- Copyright hardcpp@gmail.com
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

-- =======================================================
-- Methods
-- =======================================================

function Parsers.ResetCacheID(p_Node)

end

-- Init parsers, this method will read all parsers present in the gamefolder
function Parsers.Init()
    local l_Path = "Parsers\\" .. Parsers.Folder .. "\\"
    for l_Key,l_Value in pairs(PacketStudio.PacketTypes) do
        local l_File = io.open(l_Path .. l_Value[3] .. ".psp", "r")

        if l_File~=nil then
            Parsers.ListCache[l_Key] = Helpers.TableUnserialize(l_File:read("*all"))
            io.close(l_File)
        else
            Parsers.ListCache[l_Key] = nil;
        end
    end
end

-- Create a new parser
-- @p_Value : Packet type
-- @p_Name  : Packet name
function Parsers.Create(p_Value, p_Name)
	os.execute("mkdir " .. "Parsers");
	os.execute("mkdir " .. "Parsers\\" .. Parsers.Folder);

    local l_Path = "Parsers\\" .. Parsers.Folder .. "\\" .. p_Name .. ".psp"

    local l_File = io.open(l_Path, "w+")
    l_File:write(Helpers.TableSerialize( {} ))
    l_File:close()

    Parsers.ListCache[p_Value] = { };
end

-- Delete a packet parser
-- @p_Value : Packet type
-- @p_Name  : Packet name
function Parsers.Delete(p_Value, p_Name)
    local l_Path = "Parsers\\" .. Parsers.Folder .. "\\" .. p_Name .. ".psp"
    os.remove(l_Path)

    Parsers.ListCache[p_Value] = nil;
end

-- Save a packet parser
-- @p_Value : Packet type
function Parsers.Save(p_Value)
    local l_Path = "Parsers\\" .. Parsers.Folder .. "\\" .. PacketStudio.PacketTypes[p_Value][3] .. ".psp"

    local l_File = io.open(l_Path, "w+")
    l_File:write(Helpers.TableSerialize(Parsers.ListCache[p_Value]))
    l_File:close()
end