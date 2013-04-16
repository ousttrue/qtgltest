------------------------------------------------------------------------------
-- Solution
------------------------------------------------------------------------------
solution "qtgltest"
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

configuration "gmake"
do
    buildoptions {
        "-Wall",
        "-std=c++0x",
    }
end

if os.is("windows") then
    MAKE="nmake /nologo"
    QTDIR="C:/Qt/Qt5.0.2/5.0.2/msvc2010_opengl"
else
    MAKE="make"
    QTDIR=""
end

configuration "windows"
do
    includedirs {
        "glew-1.9.0/include",
        "glm-0.9.4.1/include",
    }
    libdirs {
        "glew-1.9.0/lib",
    }
end

configuration {}

include "qtgltest"
include "gls"
include "glr"

