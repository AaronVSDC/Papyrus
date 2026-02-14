workspace "Papyrus"
	architecture "x64"
	configurations{"Debug","Release"} --TODO: add a dist in the future?


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Papyrus"
	location "Papyrus"
	kind "SharedLib"
	language "C++"
	buildoptions{"/utf-8"}



	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Papyrus/Vendor/spdlog/include" 
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PPR_PLATFORM_WINDOWS",
			"PPR_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/PapyrusApp")
		}

	filter "configurations:Debug"
		defines "PPR_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PPR_RELEASE"
		optimize "On"

project "PapyrusApp"
	location "PapyrusApp"
	kind "ConsoleApp"
	language "C++"
	buildoptions{"/utf-8"} 



	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs 
	{
		"Papyrus/Vendor/spdlog/include", 
		"Papyrus/Source" 
	}

	links
	{
		"Papyrus"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PPR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PPR_DEBUG"
		symbols "On"
		 
	filter "configurations:Release"
		defines "PPR_RELEASE"
		optimize "On"
