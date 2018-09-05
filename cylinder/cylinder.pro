#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T09:21:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cylinder
TEMPLATE = app

include("../dependence/dependence.pri");

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp \
    UnizModeldata.cpp \
    formgraphics.cpp

HEADERS  += widget.h \
    openglui.h \
    UnizModeldata.h \
    UnizBoundingBoxf.h \
    UnizHalfEdge.h \
    UnizPrimitiveFunctor.h \
    formgraphics.h \
    UnizGenNormalFunctor.h \
    UnizTopologyFunctor.h \
    UnizUnifyVertFunctor.h \
    UnizCompareFuctor.h

FORMS    += widget.ui

RESOURCES += \
    shader.qrc
