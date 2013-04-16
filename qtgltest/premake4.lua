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
    "moc_scenemodel.cpp",
}

-- compile
includedirs {
    "../gls",
    "../glr",
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
        QTDIR.."/include/QtWidgets",
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
        "Qt5Cored",
        "Qt5Guid",
        "Qt5Widgetsd",
        "Qt5OpenGLd",
    }
end
configuration { "windows", "release" }
do
    links {
        "Qt5Core",
        "Qt5Gui",
        "Qt5Widgets",
        "Qt5OpenGL",
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

