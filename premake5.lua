workspace "Europa"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories

IncludeDir = {}
IncludeDir["GLFW"] = "Europa/vendor/GLFW/include"
IncludeDir["Glad"] = "Europa/vendor/Glad/include"
IncludeDir["imgui"] = "Europa/vendor/imgui"
IncludeDir["glm"] = "Europa/vendor/glm"

include "Europa/vendor/GLFW"
include "Europa/vendor/Glad"
include "Europa/vendor/imgui"


project "Europa"
	location "Europa"
	kind "StaticLib"
	cppdialect "C++17"
	language"C++"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
		
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",

		
			
	}
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"imgui",
		
		
		
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EU_PLATFORM_WINDOWS",
			"EU_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	

	filter "configurations:Debug"
		defines "EU_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "EU_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EU_DIST"
		runtime "Release"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	staticruntime "On"
	cppdialect "C++17"

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
			"Europa/vendor/spdlog/include",
			"Europa/src",
			"%{IncludeDir.glm}",
			"Europa/vendor"

		}

		links
		{
			"Europa"
		}
	filter "system:windows"

		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EU_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EU_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EU_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EU_DIST"
		optimize "On"