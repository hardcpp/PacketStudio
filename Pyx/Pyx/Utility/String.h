#pragma once
#include "XorString.h"
#include <cstdlib>
#include <string>

namespace Pyx
{
    namespace Utility
    {
        class String
        {
            
            public:
                static std::string GetRandomString(int length)
                {
                    std::string result;
                    result.resize(length);
                    const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                    for (int i = 0; i < length; i++)
                        result[i] = alphanum[rand() % sizeof(alphanum) - 1];
                    return result;
                }

        };
    }
}
