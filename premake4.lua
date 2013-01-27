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
    QTDIR="C:/Qt/4.8.4"
else
    MAKE="make"
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

------------------------------------------------------------------------------
-- Project
------------------------------------------------------------------------------
project "qtgltest"
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
    MAKE.." -f Makefile.qt moc",
}
files {
    "moc_mainwindow.cpp",
    "moc_loggingwidget.cpp",
    "moc_glview.cpp",
    "moc_scenetreewidget.cpp",
}

-- compile
includedirs {
    "gls",
    "glr",
}
defines {
}
buildoptions {
}

-- link
links {
    "glr",
    "gls",
}
linkoptions {
}

configuration "windows"
do
    includedirs {
        QTDIR.."/include",
        QTDIR.."/include/QtCore",
        QTDIR.."/include/QtGui",
        QTDIR.."/include/QtOpenGL",
    }
    libdirs {
        QTDIR.."/lib",
    }
    links {
        "glu32",
        "glew32",
        "opengl32",
    }
end
configuration { "windows", "debug" }
do
    links {
        "QtCored4",
        "QtGuid4",
        "QtOpenGLd4",
    }
end
configuration { "windows", "release" }
do
    links {
    }
end

configuration "not windows"
do
    includedirs {
        "/usr/include/qt4",
        "/usr/include/qt4/QtCore",
        "/usr/include/qt4/QtGui",
        "/usr/include/qt4/QtOpenGL",
    }
    libdirs {
        "/usr/lib/qt4",
    }
    links {
        "QtCore",
        "QtGui",
        "QtOpenGL",
        "GLU",
        "GLEW",
    }
end


------------------------------------------------------------------------------
-- Project
------------------------------------------------------------------------------
project "gls"
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
    "gls/*.cpp", "gls/*.h",
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
    "glr/*.cpp", "glr/*.h",
}
prebuildcommands {
}

-- compile
includedirs {
    "gls",
}
defines {
}
buildoptions {
}

-- link
links {
    "gls",
}

