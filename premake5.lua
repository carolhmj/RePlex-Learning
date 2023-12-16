workspace "RePlex"
    configurations { "Debug", "Release" }
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    cppdialect "C++17"

    project "RePlexRuntime"
        kind "ConsoleApp"
        files { "runtime/**.h", "runtime/**.cpp" }
        includedirs { "lib/pub" , "test/pub" }
    
    project "RePlexTest"
        kind "SharedLib"
        files { "test/**.h", "test/**.cpp", "test/pub/*.h" }
        includedirs { "lib/pub" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
    