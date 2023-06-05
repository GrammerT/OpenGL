
QT += opengl

INCLUDEPATH += "$$PWD/OpenglLib/glut/include"
INCLUDEPATH += "$$PWD/OpenglLib/glew-2.1.0/include"
INCLUDEPATH += "$$PWD/OpenglLib/glfw-3.3.8/include"



CONFIG(debug, debug|release){
win32{
contains(QMAKE_TARGET.arch, x86){
    DESTDIR=../debug_x86/
    }
contains(QMAKE_TARGET.arch, x86_64){
    DESTDIR=../debug_x64/
    LIBS += -lopengl32 -lglu32
    LIBS += "$$PWD/OpenglLib/glut/debug/glut32.lib"
    LIBS += "$$PWD/OpenglLib/glfw-3.3.8/lib-vc2017/glfw3dll.lib"
    LIBS += "$$PWD/OpenglLib/glew-2.1.0/lib/Release/x64/glew32.lib"
}
}
}

CONFIG(release, debug|release){
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
win32{
contains(QMAKE_TARGET.arch, x86){
    DESTDIR=../release_x86/

    }
contains(QMAKE_TARGET.arch, x86_64){
    DESTDIR=../release_x64/
    LIBS += -lopengl32 -lglu32
    LIBS += "$$PWD/OpenglLib/glut/release/glut32.lib"
    LIBS += "$$PWD/OpenglLib/glfw-3.3.8/lib-vc2017/glfw3dll.lib"
    LIBS += "$$PWD/OpenglLib/glew-2.1.0/lib/Release/x64/glew32.lib"
    }
}
}
