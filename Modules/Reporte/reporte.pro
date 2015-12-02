#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T23:25:16
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reporte
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    generadorreporte.cpp \
    ../../GUI/test/Auditoria.cpp \
    ../../GUI/test/Competencia.cpp \
    ../../GUI/test/Deporte.cpp \
    ../../GUI/test/Disponibilidad.cpp \
    ../../GUI/test/Doc.cpp \
    ../../GUI/test/estado.cpp \
    ../../GUI/test/GestorBaseDatos.cpp \
    ../../GUI/test/GestorCompetencias.cpp \
    ../../GUI/test/GestorLugares.cpp \
    ../../GUI/test/GestorPartidos.cpp \
    ../../GUI/test/GestorUsuarios.cpp \
    ../../GUI/test/HistorialParticipante.cpp \
    ../../GUI/test/Localidad.cpp \
    ../../GUI/test/Lugar.cpp \
    ../../GUI/test/Modalidad.cpp \
    ../../GUI/test/Pais.cpp \
    ../../GUI/test/Participante.cpp \
    ../../GUI/test/Partido.cpp \
    ../../GUI/test/Provincia.cpp \
    ../../GUI/test/Puntaje.cpp \
    ../../GUI/test/Puntos.cpp \
    ../../GUI/test/res.cpp \
    ../../GUI/test/Resultado.cpp \
    ../../GUI/test/Set.cpp \
    ../../GUI/test/Sets.cpp \
    ../../GUI/test/tipomodalidad.cpp \
    ../../GUI/test/tiporesultado.cpp \
    ../../GUI/test/Usuario.cpp


HEADERS  += mainwindow.h \
    generadorreporte.h \
    ../../GUI/test/Atributo.h \
    ../../GUI/test/Auditoria.h \
    ../../GUI/test/Competencia.h \
    ../../GUI/test/Deporte.h \
    ../../GUI/test/Disponibilidad.h \
    ../../GUI/test/Doc.h \
    ../../GUI/test/dtos.h \
    ../../GUI/test/estado.h \
    ../../GUI/test/GestorBaseDatos.h \
    ../../GUI/test/GestorBaseDatosSaveEspeciales.h \
    ../../GUI/test/GestorCompetencias.h \
    ../../GUI/test/GestorLugares.h \
    ../../GUI/test/GestorPartidos.h \
    ../../GUI/test/GestorUsuarios.h \
    ../../GUI/test/HistorialParticipante.h \
    ../../GUI/test/Localidad.h \
    ../../GUI/test/Lugar.h \
    ../../GUI/test/Modalidad.h \
    ../../GUI/test/Pais.h \
    ../../GUI/test/Participante.h \
    ../../GUI/test/Partido.h \
    ../../GUI/test/Provincia.h \
    ../../GUI/test/Puntaje.h \
    ../../GUI/test/Puntos.h \
    ../../GUI/test/res.h \
    ../../GUI/test/Resultado.h \
    ../../GUI/test/Set.h \
    ../../GUI/test/Sets.h \
    ../../GUI/test/tipomodalidad.h \
    ../../GUI/test/tiporesultado.h \
    ../../GUI/test/Usuario.h

FORMS    += mainwindow.ui

RESOURCES += res.qrc

include($$PWD/QtRptProject/QtRPT/QtRPT.pri)
