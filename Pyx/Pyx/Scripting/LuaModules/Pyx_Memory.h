#pragma once
#include <Pyx/Scripting/Script.h>
#include <Shlwapi.h>

namespace LuaModules
{
    namespace Pyx_Memory
    {

        template <typename T>
        T Read(uintptr_t ptr)
        {
            T result;
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ptr, (LPVOID)&result, sizeof(T), nullptr);
            return result;
        }

        inline std::string ReadASCIIString(uintptr_t ptr, size_t length = 128)
        {
            auto* buffer = new char[length];
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ptr, (LPVOID)buffer, length, nullptr);
            auto result = std::string(buffer, strlen(buffer));
            delete[] buffer;
            return result;
        }

        inline std::wstring ReadUTF16String(uintptr_t ptr, size_t length = 128)
        {
            auto* buffer = new wchar_t[length];
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ptr, (LPVOID)buffer, length * sizeof(wchar_t), nullptr);
            auto result = std::wstring(buffer, wcslen(buffer));
            delete[] buffer;
            return result;
        }

        inline std::vector<uint8_t> ReadBytes(uintptr_t ptr, size_t length)
        {
            std::vector<uint8_t> results = std::vector<uint8_t>(length);
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ptr, (LPVOID)&results[0], length, nullptr);
            return results;
        }

        inline void BindToScript(Pyx::Scripting::Script* pScript)
        {

            LuaBinding(pScript->GetLuaState()).beginModule("Pyx")
                .beginModule("Memory")
                .addFunction("ReadPointer", [](uintptr_t ptr) { return Read<uintptr_t>(ptr); })
                .addFunction("ReadInt8", [](uintptr_t ptr) { return Read<int8_t>(ptr); })
                .addFunction("ReadUInt8", [](uintptr_t ptr) { return Read<uint8_t>(ptr); })
                .addFunction("ReadInt16", [](uintptr_t ptr) { return Read<int16_t>(ptr); })
                .addFunction("ReadUInt16", [](uintptr_t ptr) { return Read<uint16_t>(ptr); })
                .addFunction("ReadInt32", [](uintptr_t ptr) { return Read<int32_t>(ptr); })
                .addFunction("ReadUInt32", [](uintptr_t ptr) { return Read<uint32_t>(ptr); })
                .addFunction("ReadInt64", [](uintptr_t ptr) { return Read<int64_t>(ptr); })
                .addFunction("ReadUInt64", [](uintptr_t ptr) { return Read<uint64_t>(ptr); })
                .addFunction("ReadFloat", [](uintptr_t ptr) { return Read<float>(ptr); })
                .addFunction("ReadBytes", ReadBytes)
                .addFunction("ReadASCIIString", ReadASCIIString, LUA_ARGS(uintptr_t, _def<size_t, 128>))
                .addFunction("ReadUTF16String", ReadUTF16String, LUA_ARGS(uintptr_t, _def<size_t, 128>));

        }

    }
}
