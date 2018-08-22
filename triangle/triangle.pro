#-------------------------------------------------
#
# Project created by QtCreator 2018-08-22T14:55:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = triangle
TEMPLATE = app


include("../dependence/dependence.pri")

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp

HEADERS  += widget.h \
    openglui.h

FORMS    += widget.ui
