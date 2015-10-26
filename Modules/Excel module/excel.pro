#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T22:45:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = excel
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

include(qtxlsx/src/xlsx/qtxlsx.pri)
