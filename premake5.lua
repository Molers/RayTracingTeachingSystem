workspace "imgui_glfw3_raytracing_T_M_S"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Molers/vendor/GLFW/include"
IncludeDir["glad"] = "Molers/vendor/glad/include"
IncludeDir["imgui"] = "Molers/vendor/imgui"

include "Molers/vendor/GLFW"
include "Molers/vendor/glad"
include "Molers/vendor/imgui"

project "Molers"
	location"Molers"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Precompile.h"
	pchsource "Molers/src/Precompile.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{	"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}

	links 
	{ 
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MOLERS_PLATFORM_WINDOWS",
			"MOLERS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Games")
		}
	filter "configurations:Debug"
		defines "MOLERS_Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MOLERS_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MOLERS_DIST"
		buildoptions "/MD"
		optimize "On"
	

project "Games"
	location"Games"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Molers/vendor/spdlog/include",
		"Molers/src"
	}

	links
	{
		"Molers"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines
		{
			"MOLERS_PLATFORM_WINDOWS",
		}

	
	filter "configurations:Debug"
		defines "MOLERS_Debug"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MOLERS_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MOLERS_DIST"
		buildoptions "/MD"
		optimize "On"
	