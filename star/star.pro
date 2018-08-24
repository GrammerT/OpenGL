#-------------------------------------------------
#
# Project created by QtCreator 2018-08-24T17:09:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = star
TEMPLATE = app

include("../dependence/dependence.pri")

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp

HEADERS  += widget.h \
    openglui.h

FORMS    += widget.ui
