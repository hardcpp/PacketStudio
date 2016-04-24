#pragma once
#include <Windows.h>
#include <sstream>
#include "Utility/XorString.h"

#define PYX_ASSERT_A(cond) if (!(cond)) { std::stringstream ss; ss << XorStringA("Assertion : ") << XorStringA(#cond) << XorStringA("\r\nFile : ") << XorStringA(__FILE__) << XorStringA("\r\nLine : ") << __LINE__; MessageBoxA(nullptr, ss.str().c_str(), XorStringA("Assertion failure"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1); }
#define PYX_ASSERT_W(cond) if (!(cond)) { std::stringstream ss; ss << XorStringW(L"Assertion : ") << XorStringW(#cond) << XorStringA(L"\r\nFile : ") << XorStringW(__FILE__) << XorStringW(L"\r\nLine : ") << __LINE__; MessageBoxW(nullptr, ss.str().c_str(), XorStringW(L"Assertion failure"), MB_ICONERROR); TerminateProcess(GetCurrentProcess(), -1); }
