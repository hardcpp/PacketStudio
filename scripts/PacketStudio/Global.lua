-- Packet studio
-- Copyright hardcpp@gmail.com 2016-2017
-- https://github.com/hardcpp/PacketStudio

GlobalEnums = {}
Helpers = {}
PacketStudio = {}

-- Setup global
PacketStudio.Views          = {}
PacketStudio.PacketTypes    = {}
PacketStudio.Enums          = {}

-- Packet direction
GlobalEnums.PacketDirection = {
    SERVER_TO_CLIENT = 1,
    CLIENT_TO_SERVER = 2
}

-- =======================================================
-- Helpers
-- =======================================================

function Helpers.NumToHex(p_Num, p_Size)
    local l_HexSymbols = '0123456789ABCDEF'
    local l_Result     = ''

    while p_Num > 0 do
        local l_Mod = math.fmod(p_Num, 16)
        l_Result = string.sub(l_HexSymbols, l_Mod+1, l_Mod+1) .. l_Result
        p_Num = math.floor(p_Num / 16)
    end

    if l_Result == '' then
        l_Result = '0'
    end

    while l_Result:len() < p_Size do
        l_Result = "0" .. l_Result
    end

    return l_Result
end

function BuildColor(p_R, p_G, p_B, p_A)


end

function Helpers.TableCopy(p_Original)
    local l_OriginalType = type(p_Original)
    local l_Copy

    if l_OriginalType == 'table' then
        l_Copy = {}
        for l_OriginalKey, l_OriginalValue in next, p_Original, nil do
            l_Copy[Helpers.TableCopy(l_OriginalKey)] = Helpers.TableCopy(l_OriginalValue)
        end
        setmetatable(l_Copy, Helpers.TableCopy(getmetatable(p_Original)))
    else -- number, string, boolean, etc
        l_Copy = p_Original
    end

    return l_Copy
end

-- =======================================================
-- Table serialization
-- =======================================================

local g_SerializeTable = {}

-- Call apropriated serializer
local function Serialize_Do(...)
    return g_SerializeTable[type(...)](...)
end

-- Serialization method template
-- @p_Function : Method template
local function Serialize_Template(p_Function)
    return function(p_D, p_Code, p_Var)
        if p_Var[p_D] == nil then
            p_Var[1]      = p_Var[1] + 1
            p_Var[p_D]    = ("_[%d]"):format(p_Var[1])

            local l_Index = #p_Code+1

            p_Code[l_Index] = "" -- Reserve place during recursion
            p_Code[l_Index] = ("%s=%s"):format(p_Var[p_D], p_Function(p_D, p_Code, p_Var))
        end

        return p_Var[p_D]
    end
end

-- Serialize a table
-- @p_Table : Table to serialize
-- @p_Code  : Output code
-- @p_Var   : Code generating
local function Serialize_Table(p_Table, p_Code, p_Var)
    for l_Key, l_Value in pairs(p_Table) do
        local l_KeySerialized   = Serialize_Do(l_Key, p_Code, p_Var)
        local l_ValueSerialized = Serialize_Do(l_Value, p_Code, p_Var)

        p_Code[#p_Code+1] = ("%s[%s]=%s"):format(p_Var[p_Table], l_KeySerialized, l_ValueSerialized)
    end

    return "{}"
end

-- Serialize a char
-- @p_Char : Char to serialize
local function Serialize_StringChar(p_Char)
    return ("\\%3d"):format(p_Char:byte())
end

-- Serialize a string
-- @p_String : String to serialize
local function Serialize_String(p_String)
    return ('"%s"'):format(p_String:gsub("[^ !#-~]", Serialize_StringChar))
end

g_SerializeTable["nil"]      = tostring
g_SerializeTable["boolean"]  = tostring
g_SerializeTable["number"]   = tostring
g_SerializeTable["string"]   = Serialize_String
g_SerializeTable["table"]    = Serialize_Template(Serialize_Table)

-- =======================================================
-- =======================================================

-- Serialize a table
-- @p_Table : Table to serialize
function Helpers.TableSerialize(p_Table)
    local l_Code    = { "local _ = {}" }
    local l_Value   = Serialize_Do(p_Table, l_Code, {0})

    l_Code[#l_Code+1] = "return ".. l_Value

    if #l_Code == 2 then
        return l_Code[2]
    else
        return table.concat(l_Code, "\n")
    end
end

-- Unserialize a table
-- @p_Table : Table to serialize
function Helpers.TableUnserialize(p_Data)
    l_Function = load(p_Data)

    if l_Function ~= nil then
        return l_Function()
    end

    return { }
end