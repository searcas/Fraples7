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
IncludeDir ["glm"] = "FraplesSeven/Vendor/glm"
IncludeDir ["stb_image"] = "FraplesSeven/Vendor/stb_image"





group "Dependencies"
    include "FraplesSeven/vendor/GLFW"
    include "FraplesSeven/vendor/Glad"
    include "FraplesSeven/vendor/imgui"

group ""




project "FraplesSeven"
    location "FraplesSeven"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")
                    
    -- PRE COMPAILED HEADER
    pchheader "FplPCH.h"
    pchsource "FraplesSeven/src/FplPCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Vendor/stb_image/**.cpp",
        "%{prj.name}/Vendor/stb_image/**.h",
        "%{prj.name}/Vendor/glm/glm/**.hpp",
        "%{prj.name}/Vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/Vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.imGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"

    }

    links
    {
        "GLFW",
        "GLAD",
        "imGui",
        "opengl32.lib"
    }
    filter "system:windows"
        systemversion "latest"

    defines
    {
        "FPL_PLATFORM_WINDOWS",
        "FPL_BUILD_DLL",
        "GLFW_INCLUDE_NONE"
    }



    filter "configurations:Debug"
        defines"FPL_DEBUG"
        runtime "Debug"
        symbols "on"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
        runtime "Release"
        optimize "on"
    
    filter "configurations:Dist"
        defines"FPL_DIST"
        runtime "Release"
        optimize "on"

        

project "SandBox"
    location "SandBox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

                
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
        "FraplesSeven/src",
        "FraplesSeven/Vendor/",
        "%{IncludeDir.glm}"
        
    }


    links
    {
        "FraplesSeven"
    }



        filter "system:windows"
        systemversion "latest"
    

    defines
    {
        "FPL_PLATFORM_WINDOWS",
    }



    filter "configurations:Debug"
        defines"FPL_DEBUG"
        runtime "Debug"
        symbols "on"
            
    filter "configurations:Release"
        defines"FPL_RELEASE"
        runtime "Release"
            optimize "on"


    filter "configurations:Dist"
        defines"FPL_DIST"
        runtime "Release"
            optimize "on"
------------------------------------------------------------