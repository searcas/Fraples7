workspace "FraplesSeven"
    architecture "x64"
	startproject "SandBox"

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
IncludeDir ["GLAD"] = "FraplesSeven/Vendor/GLAD/include"
IncludeDir ["imGui"] = "FraplesSeven/Vendor/imGui"

include "FraplesSeven/Vendor/GLFW"
include "FraplesSeven/Vendor/GLAD"
include "FraplesSeven/Vendor/imGui"





project "FraplesSeven"
    location "FraplesSeven"
        kind "SharedLib"
            language "C++"
            staticruntime "off"
                
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imGui}"

    }
	links
	{
		"GLFW",
		"GLAD",
		"imGui",
		"opengl32.lib"
	}
        filter "system:windows"
            cppdialect "C++17"
                systemversion "latest"

    defines
    {
        "FPL_PLATFORM_WINDOWS",
        "FPL_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandBox/\"")
    }

    filter "configurations:Debug"
        defines"FPL_DEBUG"
        runtime "Debug"
        symbols "On"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
        runtime "Release"
        optimize "On"
    
    filter "configurations:Dist"
        defines"FPL_DIST"
        runtime "Release"
            optimize "On"

        

project "SandBox"
    location "SandBox"
        kind "ConsoleApp"
            language "C++"
            staticruntime "off"

                
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
                systemversion "latest"
    

    defines
    {
        "FPL_PLATFORM_WINDOWS",
    }



    filter "configurations:Debug"
        defines"FPL_DEBUG"
		runtime "Debug"
        symbols "On"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
		runtime "Release"
            optimize "On"
    
    filter "configurations:Dist"
        defines"FPL_DIST"
		runtime "Release"
            optimize "On"
			
		
------------------------------------------------------------


   
