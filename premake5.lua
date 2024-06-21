-- premake5.lua
workspace "TIPE"
    configurations { "Debug", "Release" }

project "Application"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    files { "./src/**.hpp", "./src/**.cpp"}   

    links {
        "mingw32",
        "SDL2main", 
        "SDL2"
    }
    
    linkoptions { "-mwindows", "-mconsole"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
