#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T09:41:50
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = block
TEMPLATE = app

include("../dependence/dependence.pri");

SOURCES += main.cpp\
        widget.cpp \
    openglwidget.cpp

HEADERS  += widget.h \
    openglwidget.h

FORMS    += widget.ui


