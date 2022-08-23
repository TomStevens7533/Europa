workspace "Europa"
	architecture "x64"
	startproject "Game"
	toolset ("v143")
	
	warnings "High"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories

IncludeDir = { }
IncludeDir["GLFW"] = "Europa/vendor/GLFW/include"
IncludeDir["Glad"] = "Europa/vendor/Glad/include"
IncludeDir["imgui"] = "Europa/vendor/imgui"
IncludeDir["glm"] = "Europa/vendor/glm"
IncludeDir["stb_image"] = "Europa/vendor/stb_image"
IncludeDir["vld"] = "Europa/vendor/VLD"
IncludeDir["rapidjson"] = "Europa/vendor/rapidjson"

include "Europa/vendor/GLFW"
include "Europa/vendor/Glad"
include "Europa/vendor/imgui"


project "Europa"
	location "Europa"
	kind "StaticLib"
	cppdialect "C++17"
	language"C++"
	staticruntime "On"
	toolset ("v143")
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/VLD/**.h",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl",
		"%{prj.name}/vendor/rapidjson/rapidjson.h",
		
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
		"%{IncludeDir.stb_image}"
	

		
			
	}
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"imgui"
		
		
		
	}
	filter "files:%{prj.name}/vendor/glm/glm/**.hpp"
		warnings "Off"
	
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

project "Europe-Editor"
	location "Europe-Editor"
	kind "ConsoleApp"
	staticruntime "On"
	cppdialect "C++17"
	toolset ("v143")

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
			"Europa",
			"Europa/vendor/VLD/vld.lib"
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



project "Game"
	location "Game"
	kind "ConsoleApp"
	staticruntime "On"
	cppdialect "C++17"
	toolset ("v143")

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
			"Europa",
			"Europa/vendor/VLD/vld_x64.lib",
			"Europa/vendor/VLD/vld.lib"
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
	