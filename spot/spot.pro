#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T09:35:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spot
TEMPLATE = app

include("../dependence/dependence.pri");

SOURCES += main.cpp\
        widget.cpp \
    opengglwidget.cpp

HEADERS  += widget.h \
    opengglwidget.h

FORMS    += widget.ui
