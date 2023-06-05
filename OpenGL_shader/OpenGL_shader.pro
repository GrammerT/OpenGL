TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        Shader.cpp \
        main.cpp

INCLUDEPATH += "D:\workspace\OpenGL\glfw-3.3.8\include\GLFW"
INCLUDEPATH += "D:\workspace\OpenGL\glew-2.1.0\include"


LIBS+="D:\workspace\OpenGL\glfw-3.3.8\lib-vc2017\glfw3dll.lib"
LIBS+="D:\workspace\OpenGL\glew-2.1.0\lib\Release\x64\glew32.lib"

LIBS+= -lopengl32

HEADERS += \
    Shader.h \
    stb_image.h

RESOURCES += \
    res.qrc

DISTFILES += \
    test.vert
