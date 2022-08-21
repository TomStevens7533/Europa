project "Glad"
    kind "StaticLib"
    language "C"
    toolset ("v143")
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	warnings "Off"
	
	files
	{
        "include/glad/glad.h",
	"include/KHR/khrplatform.h",
	"src/glad.c"
  
 	 }
	includedirs
	{
	"include"
	}
    
	filter "system:windows"
       
        systemversion "latest"
        staticruntime "On"
        

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
