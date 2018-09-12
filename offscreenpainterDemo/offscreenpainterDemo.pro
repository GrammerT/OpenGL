#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T12:08:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = offscreenpainterDemo
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        widget.cpp \
    opengloffscreensurface.cpp \
    examplepaintsurface.cpp

HEADERS  += widget.h \
    opengloffscreensurface.h \
    examplepaintsurface.h

FORMS    += widget.ui
