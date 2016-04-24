#pragma once

//-------------------------------------------------------------//
// "Malware related compile-time hacks with C++11" by LeFF   //
// You can use this code however you like, I just don't really //
// give a shit, but if you feel some respect for me, please //
// don't cut off this comment when copy-pasting... ;-)       //
//-------------------------------------------------------------//

////////////////////////////////////////////////////////////////////
template <int X> struct EnsureCompileTime {
    enum : int {
        Value = X
    };
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
//Use Compile-Time as seed
#define Seed ((__TIME__[7] - '0') * 1  + (__TIME__[6] - '0') * 10  + \
              (__TIME__[4] - '0') * 60   + (__TIME__[3] - '0') * 600 + \
              (__TIME__[1] - '0') * 3600 + (__TIME__[0] - '0') * 36000)
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
constexpr int LinearCongruentGenerator(int Rounds) {
    return 1013904223 + 1664525 * ((Rounds> 0) ? LinearCongruentGenerator(Rounds - 1) : Seed & 0xFFFFFFFF);
}
#define Random() EnsureCompileTime<LinearCongruentGenerator(10)>::Value //10 Rounds
#define RandomNumber(Min, Max) (Min + (Random() % (Max - Min + 1)))
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <int... Pack> struct IndexList {};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <typename IndexList, int Right> struct Append;
template <int... Left, int Right> struct Append<IndexList<Left...>, Right> {
    typedef IndexList<Left..., Right> Result;
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
template <int N> struct ConstructIndexList {
    typedef typename Append<typename ConstructIndexList<N - 1>::Result, N - 1>::Result Result;
};
template <> struct ConstructIndexList<0> {
    typedef IndexList<> Result;
};
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
const char XORKEY_A = static_cast<char>(0x13);
const wchar_t XORKEY_W = static_cast<wchar_t>(0x133);

constexpr char EncryptCharacterA(const char Character, int Index) {
    return Character ^ (XORKEY_A + Index);
}

template <typename IndexList> class CXorStringA;
template <int... Index> class CXorStringA<IndexList<Index...> > {
private:
    char Value[sizeof...(Index)+1];
public:
    constexpr CXorStringA(const char* const String)
        : Value{ EncryptCharacterA(String[Index], Index)... } {}

    char* decrypt() {
        for (int t = 0; t < sizeof...(Index); t++) {
            Value[t] = Value[t] ^ (XORKEY_A + t);
        }
        Value[sizeof...(Index)] = '\0';
        return Value;
    }

    char* get() {
        return Value;
    }
};

constexpr wchar_t EncryptCharacterW(const wchar_t Character, int Index) {
    return Character ^ (XORKEY_W + Index);
}

template <typename IndexList> class CXorStringW;
template <int... Index> class CXorStringW<IndexList<Index...> > {
private:
    wchar_t Value[sizeof...(Index)+1];
public:
    constexpr CXorStringW(const wchar_t* const String)
        : Value{ EncryptCharacterW(String[Index], Index)... } {}

    wchar_t* decrypt() {
        for (int t = 0; t < sizeof...(Index); t++) {
            Value[t] = Value[t] ^ (XORKEY_W + t);
        }
        Value[sizeof...(Index)] = '\0\0';
        return Value;
    }

    wchar_t* get() {
        return Value;
    }
};

#define XorStringA( String ) ( CXorStringA<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )  
#define XorStringW( String ) ( CXorStringW<ConstructIndexList<sizeof( String ) - 1>::Result>( String ).decrypt() )  
////////////////////////////////////////////////////////////////////