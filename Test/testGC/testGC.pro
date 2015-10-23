QT += core testlib
QT -= gui

TARGET = testGC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test_cu003_listar_comp.cpp

