------------------------------------------------------------------------------
-- Solution
------------------------------------------------------------------------------
solution "sample"
configurations { "Debug", "Release" }

configuration "Debug"
do
	defines { "DEBUG" }
	flags { "Symbols", }
	targetdir "debug"
end

configuration "Release"
do
	defines { "NDEBUG" }
	flags { "Optimize", }
	targetdir "release"
end

configuration {}

------------------------------------------------------------------------------
-- Project
------------------------------------------------------------------------------
project "sample"
--language "C"
language "C++"
--kind "StaticLib"
--kind "SharedLib"
--kind "ConsoleApp"
kind "WindowedApp"

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
    "/usr/include/qt4",
    "/usr/include/qt4/QtGui",
}
defines {
}
buildoptions {
}

-- link
libdirs {
    "/usr/lib/qt4",
}
links {
    "QtCore",
    "QtGui",
}
linkoptions {
}

