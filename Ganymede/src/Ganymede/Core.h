#pragma once

#ifdef GNM_PLATFORM_WINDOWS
    #ifdef GNM_BUILD_DLL
        #define GANYMEDE_API __declspec(dllexport)
    #else
        #define GANYMEDE_API __declspec(dllimport)
    #endif
#else
    #error Ganymede currently only supports Windows
#endif

#define BIT(x) (1 << (x))
