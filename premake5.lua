workspace "FraplesSeven"
    architecture "x64"
	startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include Directories relative to root folder (solution Directory)
IncludeDir = {}
IncludeDir ["GLFW"] = "FraplesSeven/Vendor/GLFW/include"

include "FraplesSeven/Vendor/GLFW"




project "FraplesSeven"
    location "FraplesSeven"
        kind "SharedLib"
            language "C++"
                
                targetdir("bin/" .. outputdir .. "/%{prj.name}")
                objdir("bin-int/" .. outputdir .. "/%{prj.name}")
				
				-- PRE COMPAILED HEADER
				pchheader "FplPCH.h"
				pchsource "FraplesSeven/src/FplPCH.cpp"
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
		"%{prj.name}/src",
        "%{prj.name}/Vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
    }
	links
	{
		"GLFW",
		"opengl32.lib"
	}
        filter "system:windows"
            cppdialect "C++17"
                staticruntime "On"
                systemversion "latest"

    defines
    {
        "FPL_PLATFORM_WINDOWS",
        "FPL_BUILD_DLL"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/SandBox")
    }

    filter "configurations:Debug"
        defines"FPL_DEBUG"
        symbols "On"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
            optimize "On"
    
    filter "configurations:Dist"
        defines"FPL_DIST"
            optimize "On"

        

project "SandBox"
    location "SandBox"
        kind "ConsoleApp"
            language "C++"
                
                targetdir("bin/".. outputdir .. "/%{prj.name}")
                objdir("bin-int/".. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs
    {
	    "FraplesSeven/Vendor/spdlog/include",
		"FraplesSeven/src"
    }
	
	links
    {
        "FraplesSeven"
    }



        filter "system:windows"
            cppdialect "C++17"
                staticruntime "On"
                systemversion "latest"
    

    defines
    {
        "FPL_PLATFORM_WINDOWS",
    }



    filter "configurations:Debug"
        defines"FPL_DEBUG"
        symbols "On"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
            optimize "On"
    
    filter "configurations:Dist"
        defines"FPL_DIST"
            optimize "On"
			
		
------------------------------------------------------------


   