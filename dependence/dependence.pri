
QT += opengl

INCLUDEPATH += "$$PWD/OpenglLib/glut/include"


CONFIG(debug, debug|release){
win32{
contains(QMAKE_TARGET.arch, x86){
    DESTDIR=../debug_x86/
    }
contains(QMAKE_TARGET.arch, x86_64){
    DESTDIR=../debug_x64/
    LIBS += -lopengl32 -lglu32
    LIBS += "$$PWD/OpenglLib/glut/debug/glut32.lib"
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
    }
}
}
