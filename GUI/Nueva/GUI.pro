#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T08:43:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    listar_competencias.cpp \
    pantalla_usuario.cpp \
    alta_competencia.cpp \
    alta_competencia_eliminacion.cpp \
    alta_competencia_liga.cpp \
    ver_competencia.cpp \
    alta_participante.cpp \
    modificar_competencia.cpp \
    GestorBaseDatos.cpp \
    GestorCompetencias.cpp \
    GestorLugares.cpp \
    GestorParticipantes.cpp \
    GestorPartidos.cpp \
    GestorUsuarios.cpp

HEADERS  += mainwindow.h \
    listar_competencias.h \
    pantalla_usuario.h \
    alta_competencia.h \
    alta_competencia_eliminacion.h \
    alta_competencia_liga.h \
    ver_competencia.h \
    alta_participante.h \
    modificar_competencia.h \
    GestorBaseDatos.h \
    GestorCompetencias.h \
    GestorLugares.h \
    GestorParticipantes.h \
    GestorPartidos.h \
    GestorUsuarios.h

FORMS    += mainwindow.ui \
    listar_competencias.ui \
    pantalla_usuario.ui \
    alta_competencia.ui \
    alta_competencia_eliminacion.ui \
    alta_competencia_liga.ui \
    ver_competencia.ui \
    alta_participante.ui \
    modificar_competencia.ui
