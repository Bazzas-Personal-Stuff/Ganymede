#pragma once
#include <memory>

#ifdef _WIN32
    #ifdef _WIN64
        #define GNM_PLATFORM_WINDOWS        
    #else
        #error "x86 builds are not supported"
    #endif

#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported"
    #elif TARGET_OS_IPHONE == 1
        #define GNM_PLATFORM_IOS
        #error "IOS is not supported"
    #elif TARGET_OS_MAC == 1
        #define GNM_PLATFORM_MACOS
        #error "MacOS is not supported"
    #endif

#elif defined(__ANDROID__)
    #define GNM_PLATFORM_ANDROID
    #error "Android is not supported"

#elif defined(__linux__)
    #define GNM_PLATFORM_LINUX
    #error "Linux is not supported"

#else
    #error "Unknown platform"
#endif


// DLL Support
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

namespace Ganymede {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}