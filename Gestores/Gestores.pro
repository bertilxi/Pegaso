#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T09:50:59
#
#-------------------------------------------------

QT       += core
QT       += sql

QT       -= gui

TARGET = Gestores
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += GestorBaseDatos.cpp \
    GestorCompetencias.cpp \
    GestorLugares.cpp \
    GestorPartidos.cpp \
    GestorUsuarios.cpp \
    GestorParticipantes.cpp

HEADERS += GestorBaseDatos.h \
    GestorCompetencias.h \
    GestorLugares.h \
    GestorPartidos.h \
    GestorUsuarios.h \
    GestorParticipantes.h \
    GestorBaseDatosSaveEspeciales.h \
    Atributo.h
