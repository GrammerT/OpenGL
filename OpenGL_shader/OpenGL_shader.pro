
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
        Shader.cpp \
        main.cpp


include("../dependence/dependence.pri")

HEADERS += \
    Shader.h \
    stb_image.h

RESOURCES += \
    res.qrc

DISTFILES += \
    test.vert
