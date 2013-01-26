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

configuration "gmake"
do
    buildoptions {
        "-std=c++0x",
    }
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
-- qt moc
prebuildcommands {
    "make -f Makefile.qt moc",
}
files {
    "moc_mainwindow.cpp",
    "moc_loggingwidget.cpp",
    "moc_glview.cpp",
}

-- compile
includedirs {
    "/usr/include/qt4",
    "/usr/include/qt4/QtCore",
    "/usr/include/qt4/QtGui",
    "/usr/include/qt4/QtOpenGL",

    "glw",
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
    "QtOpenGL",

    "glw",
    "GLU",
}
linkoptions {
}


------------------------------------------------------------------------------
-- Project
------------------------------------------------------------------------------
project "glw"
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
    "glw/*.cpp", "glw/*.h",
}
prebuildcommands {
}

-- compile
includedirs {
}
defines {
}
buildoptions {
}

-- link
libdirs {
}
links {
}
linkoptions {
}

