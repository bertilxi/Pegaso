#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T23:25:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reporte
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    generadorreporte.cpp

HEADERS  += mainwindow.h \
    generadorreporte.h

FORMS    += mainwindow.ui

RESOURCES += res.qrc

include($$PWD/QtRptProject/QtRPT/QtRPT.pri)
