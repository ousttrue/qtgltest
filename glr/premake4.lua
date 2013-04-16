------------------------------------------------------------------------------
-- Project
------------------------------------------------------------------------------
project "glr"
--language "C"
language "C++"
kind "StaticLib"
--kind "SharedLib"
--kind "ConsoleApp"
--kind "WindowedApp"

flags {
    "Unicode",
}
files {
    "*.cpp", "*.h",
}
prebuildcommands {
}

-- compile
includedirs {
    "../gls",
}
defines {
}
buildoptions {
}

