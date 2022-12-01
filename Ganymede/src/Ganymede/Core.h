#pragma once

#ifdef GNM_PLATFORM_WINDOWS
    #ifdef GNM_DYNAMIC_LINK
        #ifdef GNM_BUILD_DLL
            #define GANYMEDE_API __declspec(dllexport)
        #else
            #define GANYMEDE_API __declspec(dllimport)
        #endif
    #else
        #define GANYMEDE_API
    #endif
#else
    #error Ganymede currently only supports Windows
#endif

#ifdef GNM_DEBUG
    #define GNM_ENABLE_ASSERTS
#endif

#ifdef GNM_ENABLE_ASSERTS
    #define GNM_ASSERT(x, ...) {if(!(x)) { GNM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
    #define GNM_CORE_ASSERT(x, ...) {if(!(x)) { GNM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
    #define GNM_ASSERT(x, ...)
    #define GNM_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << (x))
#define GNM_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
