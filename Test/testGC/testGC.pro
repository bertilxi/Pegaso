QT += core testlib
QT -= gui

TARGET = testGC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test_cu003_listar_comp.cpp \
    testgestorpartido.cpp \
    testgestorcompetencia.cpp

HEADERS += testgestorpartido.h \
    testgestorcompetencia.h

