#-------------------------------------------------
#
# Project created by QtCreator 2018-09-15T11:51:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = R_T_demo
TEMPLATE = app

include("../dependence/dependence.pri")

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp

HEADERS  += widget.h \
    openglui.h

FORMS    += widget.ui
