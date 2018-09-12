#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T17:22:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = twoModel_TSR
TEMPLATE = app

include("../dependence/dependence.pri");

SOURCES += main.cpp\
        widget.cpp \
    openglui.cpp

HEADERS  += widget.h \
    openglui.h

FORMS    += widget.ui
