#-------------------------------------------------
#
# Project created by QtCreator 2015-10-24T22:45:32
#
#-------------------------------------------------

QT       += core gui widgets network sql

TARGET = excel
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    generadorexcel.cpp \
    ../../Gestores/Auditoria.cpp \
    ../../Gestores/Competencia.cpp \
    ../../Gestores/Deporte.cpp \
    ../../Gestores/Disponibilidad.cpp \
    ../../Gestores/Doc.cpp \
    ../../Gestores/estado.cpp \
    ../../Gestores/GestorBaseDatos.cpp \
    ../../Gestores/GestorCompetencias.cpp \
    ../../Gestores/GestorLugares.cpp \
    ../../Gestores/GestorPartidos.cpp \
    ../../Gestores/GestorUsuarios.cpp \
    ../../Gestores/HistorialParticipante.cpp \
    ../../Gestores/Localidad.cpp \
    ../../Gestores/Lugar.cpp \
    ../../Gestores/Modalidad.cpp \
    ../../Gestores/Pais.cpp \
    ../../Gestores/Participante.cpp \
    ../../Gestores/Partido.cpp \
    ../../Gestores/Provincia.cpp \
    ../../Gestores/Puntaje.cpp \
    ../../Gestores/Puntos.cpp \
    ../../Gestores/res.cpp \
    ../../Gestores/Resultado.cpp \
    ../../Gestores/Set.cpp \
    ../../Gestores/Sets.cpp \
    ../../Gestores/tipomodalidad.cpp \
    ../../Gestores/tiporesultado.cpp \
    ../../Gestores/Usuario.cpp
HEADERS += generadorexcel.h \
    ../../Gestores/Atributo.h \
    ../../Gestores/Auditoria.h \
    ../../Gestores/Competencia.h \
    ../../Gestores/Deporte.h \
    ../../Gestores/Disponibilidad.h \
    ../../Gestores/Doc.h \
    ../../Gestores/dtos.h \
    ../../Gestores/estado.h \
    ../../Gestores/GestorBaseDatos.h \
    ../../Gestores/GestorCompetencias.h \
    ../../Gestores/GestorLugares.h \
    ../../Gestores/GestorPartidos.h \
    ../../Gestores/GestorUsuarios.h \
    ../../Gestores/HistorialParticipante.h \
    ../../Gestores/Localidad.h \
    ../../Gestores/Lugar.h \
    ../../Gestores/Modalidad.h \
    ../../Gestores/Pais.h \
    ../../Gestores/Participante.h \
    ../../Gestores/Partido.h \
    ../../Gestores/Provincia.h \
    ../../Gestores/Puntaje.h \
    ../../Gestores/Puntos.h \
    ../../Gestores/res.h \
    ../../Gestores/Resultado.h \
    ../../Gestores/Set.h \
    ../../Gestores/Sets.h \
    ../../Gestores/tipomodalidad.h \
    ../../Gestores/tiporesultado.h \
    ../../Gestores/Usuario.h

include(qtxlsx/src/xlsx/qtxlsx.pri)

