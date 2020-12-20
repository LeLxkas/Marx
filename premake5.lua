workspace "Marx"
	architecture "x64"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Marx"
	location "Marx"
	kind "SharedLib"
	language "C++"
	characterset "MBCS"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mxpch.h"
	pchsource "Marx/src/mxpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"MX_PLATFORM_WINDOWS",
			"MX_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines {
		    "MX_DEBUG",
			"MX_ENABLE_ASSERTS",
			"MX_USE_CONDITIONAL_EXCEPT"
		}
		symbols "On"

	filter "configurations:Release"
		defines "MX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MX_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	characterset "MBCS"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Marx/vendor/spdlog/include",
		"Marx/src"
	}

	links {
		"Marx"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"MX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
		    "MX_DEBUG",
			"MX_ENABLE_ASSERTS",
			"MX_USE_CONDITIONAL_EXCEPT"
		}
		symbols "On"

	filter "configurations:Release"
		defines "MX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MX_DIST"
		optimize "On"
