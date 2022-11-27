workspace "Ganymede"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ganymede/vendor/GLFW/include"

include "Ganymede/vendor/GLFW" -- Premake submodule include

project "Ganymede"
    location "Ganymede"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gnmpch.h"
    pchsource "Ganymede/src/gnmpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS",
            "GNM_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "GNM_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "GNM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GNM_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs {
        "Ganymede/vendor/spdlog/include",
        "Ganymede/src"
    }
    
    links {
        "Ganymede"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "GNM_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GNM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GNM_DIST"
        optimize "On"
