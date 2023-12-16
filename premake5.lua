workspace "RePlex"
    configurations { "Debug", "Release" }
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    cppdialect "C++17"

    project "RePlex"
        kind "SharedLib"
        files { "lib/**.h", "lib/**.cpp" }

    project "RePlexRuntime"
        kind "ConsoleApp"
        files { "runtime/**.h", "runtime/**.cpp" }
        links { "RePlex" }
        includedirs { "lib/pub" }
    
    project "RePlexTest"
        kind "SharedLib"
        files { "test/**.h", "test/**.cpp", "test/pub/*.h" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
    