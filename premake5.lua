workspace "PixelEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "PixelEngine"
	location "PixelEngine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "system:unix"

		defines
		{
			"ENGINE_PLATFORM_UNIX"
		}
	
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"

project "PathFinding"
	location "PathFinding"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PixelEngine/src"
	}

	links
	{
		"PixelEngine"
	}

	configuration "linux"
		links
		{	"X11",
			"GL",
			"pthread",
			"png"
		}

	--configuration { "linux", "gmake" }
		--buildoptions "-std=c++0x"

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "system:unix"

		defines
		{
			"ENGINE_PLATFORM_UNIX"
		}

		links
		{
			"X11",
			"GL",
			"pthread",
			"png"
		}
	
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"


project "PlayerMovement"
	location "PlayerMovement"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PixelEngine/src"
	}

	links
	{
		"PixelEngine"
	}

	configuration "linux"
		links
		{	"X11",
			"GL",
			"pthread",
			"png"
		}

	--configuration { "linux", "gmake" }
		--buildoptions "-std=c++0x"

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "system:unix"

		defines
		{
			"ENGINE_PLATFORM_UNIX"
		}

		links
		{
			"X11",
			"GL",
			"pthread",
			"png"
		}
	
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"


project "FollowPlayer"
	location "FollowPlayer"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"PixelEngine/src"
	}

	links
	{
		"PixelEngine"
	}

	configuration "linux"
		links
		{	"X11",
			"GL",
			"pthread",
			"png"
		}

	--configuration { "linux", "gmake" }
		--buildoptions "-std=c++0x"

	filter "system:windows"
		
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "system:unix"

		defines
		{
			"ENGINE_PLATFORM_UNIX"
		}

		links
		{
			"X11",
			"GL",
			"pthread",
			"png"
		}
	
	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"


