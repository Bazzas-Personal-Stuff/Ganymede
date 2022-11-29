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
IncludeDir["Glad"] = "Ganymede/vendor/Glad/include"
IncludeDir["ImGui"] = "Ganymede/vendor/imgui"

-- Premake submodule includes
group "Dependencies"
    include "Ganymede/vendor/GLFW" 
    include "Ganymede/vendor/Glad"
    include "Ganymede/vendor/imgui"

group ""

project "Ganymede"
    location "Ganymede"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS",
            "GNM_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "GNM_DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "GNM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "GNM_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "GNM_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "GNM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "GNM_DIST"
        runtime "Release"
        optimize "On"
