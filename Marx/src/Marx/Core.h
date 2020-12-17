#pragma once

#ifdef MX_PLATFORM_WINDOWS
    #ifdef MX_BUILD_DLL
        #define MARX_API __declspec(dllexport)
    #else
        #define MARX_API __declspec(dllimport)
    #endif
#else
    #error Marx only supports Windows!
#endif