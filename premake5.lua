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
IncludeDir["glm"] = "Ganymede/vendor/glm"
IncludeDir["stb_image"] = "Ganymede/vendor/stb_image"

-- Premake submodule includes
group "Dependencies"
    include "Ganymede/vendor/GLFW" 
    include "Ganymede/vendor/Glad"
    include "Ganymede/vendor/imgui"

group ""

project "Ganymede"
    location "Ganymede"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gnmpch.h"
    pchsource "Ganymede/src/gnmpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        --"%{prj.name}/vendor/glm/glm/**.h",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS",
            "GNM_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

        -- postbuildcommands {
        --     ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        -- }

    filter "configurations:Debug"
        defines "GNM_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "GNM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "GNM_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        --"%{prj.name}/vendor/glm/glm/**.hpp",
        --"%{prj.name}/vendor/glm/glm/**.inl",
    }
    
    includedirs {
        "Ganymede/vendor/spdlog/include",
        "Ganymede/src",
        "Ganymede/vendor",
        "%{IncludeDir.glm}",
    }
    
    links {
        "Ganymede"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "GNM_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "GNM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "GNM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "GNM_DIST"
        runtime "Release"
        optimize "on"
