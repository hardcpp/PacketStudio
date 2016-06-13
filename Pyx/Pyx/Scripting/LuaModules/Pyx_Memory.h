#pragma once
#include <Pyx/Scripting/Script.h>
#include <Shlwapi.h>

namespace LuaModules
{
    // Using Read/WriteProcessMemory here because I don't want script to crash the game :p
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
			auto strLength = strlen(buffer);
            auto result = std::string(buffer, strLength < length ? strLength : length);
            delete[] buffer;
            return result;
        }

        inline std::wstring ReadUTF16String(uintptr_t ptr, size_t length = 128)
        {
            auto* buffer = new wchar_t[length];
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)ptr, (LPVOID)buffer, length * sizeof(wchar_t), nullptr);
			auto strLength = wcslen(buffer);
            auto result = std::wstring(buffer, strLength < length ? strLength : length);
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

            LuaBinding(pScript->GetLuaState()).beginModule(XorStringA("Pyx"))
                .beginModule(XorStringA("Memory"))
                .addFunction(XorStringA("ReadPointer"), [](uintptr_t ptr) { return Read<uintptr_t>(ptr); })
                .addFunction(XorStringA("ReadInt8"), [](uintptr_t ptr) { return Read<int8_t>(ptr); })
                .addFunction(XorStringA("ReadUInt8"), [](uintptr_t ptr) { return Read<uint8_t>(ptr); })
                .addFunction(XorStringA("ReadInt16"), [](uintptr_t ptr) { return Read<int16_t>(ptr); })
                .addFunction(XorStringA("ReadUInt16"), [](uintptr_t ptr) { return Read<uint16_t>(ptr); })
                .addFunction(XorStringA("ReadInt32"), [](uintptr_t ptr) { return Read<int32_t>(ptr); })
                .addFunction(XorStringA("ReadUInt32"), [](uintptr_t ptr) { return Read<uint32_t>(ptr); })
                .addFunction(XorStringA("ReadInt64"), [](uintptr_t ptr) { return Read<int64_t>(ptr); })
                .addFunction(XorStringA("ReadUInt64"), [](uintptr_t ptr) { return Read<uint64_t>(ptr); })
                .addFunction(XorStringA("ReadFloat"), [](uintptr_t ptr) { return Read<float>(ptr); })
                .addFunction(XorStringA("ReadBytes"), ReadBytes)
                .addFunction(XorStringA("ReadASCIIString"), ReadASCIIString, LUA_ARGS(uintptr_t, _def<size_t, 128>))
                .addFunction(XorStringA("ReadUTF16String"), ReadUTF16String, LUA_ARGS(uintptr_t, _def<size_t, 128>));

        }

    }
}
