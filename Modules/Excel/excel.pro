#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T22:45:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = excel
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    generadorexcel.cpp
HEADERS += generadorexcel.h

include(qtxlsx/src/xlsx/qtxlsx.pri)

