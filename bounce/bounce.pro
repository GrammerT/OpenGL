#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T14:15:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bounce
TEMPLATE = app

include("../dependence/dependence.pri");

SOURCES += main.cpp\
        widget.cpp \
    openglwidgets.cpp

HEADERS  += widget.h \
    openglwidgets.h

FORMS    += widget.ui
