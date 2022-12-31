#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ganymede {
    class GANYMEDE_API Log {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define GNM_CORE_TRACE(...) ::Ganymede::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GNM_CORE_INFO(...) ::Ganymede::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GNM_CORE_WARN(...) ::Ganymede::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GNM_CORE_ERROR(...) ::Ganymede::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GNM_CORE_FATAL(...) ::Ganymede::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define GNM_CORE_LOG(...) GNM_CORE_INFO(__VA_ARGS__)        // Alias

// Client log macros
#define GNM_TRACE(...) ::Ganymede::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GNM_INFO(...) ::Ganymede::Log::GetClientLogger()->info(__VA_ARGS__)
#define GNM_WARN(...) ::Ganymede::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GNM_ERROR(...) ::Ganymede::Log::GetClientLogger()->error(__VA_ARGS__)
#define GNM_FATAL(...) ::Ganymede::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define GNM_LOG(...) GNM_INFO(__VA_ARGS__)                  // Alias
