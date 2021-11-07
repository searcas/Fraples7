workspace "FraplesSeven"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "FraplesSeven/vendor/GLFW/include"
IncludeDir["Glad"] = "FraplesSeven/vendor/Glad/include"
IncludeDir["ImGui"] = "FraplesSeven/vendor/imgui"
IncludeDir["glm"] = "FraplesSeven/vendor/glm"
IncludeDir["stb_image"] = "FraplesSeven/vendor/stb_image"

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

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "FplPCH.h"
	pchsource "FraplesSeven/src/FplPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "FPL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FPL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FPL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"FraplesSeven/vendor/spdlog/include",
		"FraplesSeven/src",
		"FraplesSeven/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"FraplesSeven"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "FPL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FPL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FPL_DIST"
		runtime "Release"
		optimize "on"