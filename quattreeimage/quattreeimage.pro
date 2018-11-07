#-------------------------------------------------
#
# Project created by QtCreator 2018-11-02T09:13:06
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quattreeimage
TEMPLATE = app

LIBS += -lopengl32 -lglu32

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp \
    UnizModeldata.cpp \
    effectiverect.cpp \
    UnizWorldViewTray.cpp

HEADERS  += widget.h \
    quattree.h \
    openglui.h \
    UnizModeldata.h \
    supporttool.h \
    effectiverect.h \
    UnizWorldViewTray.h

FORMS    += widget.ui

RESOURCES += \
    shader.qrc

DISTFILES += \
    fshaderPickFace.glsl \
    vshaderPickFace.glsl
