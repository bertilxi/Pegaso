#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T01:04:31
#
#-------------------------------------------------

QT       += core gui sql network

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
    Auditoria.cpp \
    Competencia.cpp \
    Deporte.cpp \
    Disponibilidad.cpp \
    Doc.cpp \
    GestorBaseDatos.cpp \
    GestorCompetencias.cpp \
    GestorLugares.cpp \
    GestorPartidos.cpp \
    GestorUsuarios.cpp \
    HistorialParticipante.cpp \
    Localidad.cpp \
    Lugar.cpp \
    Modalidad.cpp \
    Pais.cpp \
    Participante.cpp \
    Partido.cpp \
    Provincia.cpp \
    Puntaje.cpp \
    Puntos.cpp \
    Resultado.cpp \
    Set.cpp \
    Sets.cpp \
    Usuario.cpp \
    gui.cpp \
    ver_competencia.cpp \
    pantalla_usuario.cpp \
    modificar_competencia.cpp \
    listar_competencias.cpp \
    alta_competencia.cpp \
    res.cpp \
    tipomodalidad.cpp \
    tiporesultado.cpp \
    estado.cpp \
    mostrar_fixture.cpp \
    tabla_posiciones.cpp \
    registrar_usuario.cpp \
    listar_participante.cpp \
    gestionar_fixture.cpp \
    ../../Modules/Excel/generadorexcel.cpp \
    ../../Modules/Reporte/generadorreporte.cpp

HEADERS  += Atributo.h \
    Auditoria.h \
    Competencia.h \
    Deporte.h \
    Disponibilidad.h \
    Doc.h \
    dtos.h \
    GestorBaseDatos.h \
    GestorCompetencias.h \
    GestorLugares.h \
    GestorPartidos.h \
    GestorUsuarios.h \
    HistorialParticipante.h \
    Localidad.h \
    Lugar.h \
    Modalidad.h \
    Pais.h \
    Participante.h \
    Partido.h \
    Provincia.h \
    Puntaje.h \
    Puntos.h \
    Resultado.h \
    Set.h \
    Sets.h \
    Usuario.h \
    gui.h \
    ver_competencia.h \
    pantalla_usuario.h \
    modificar_competencia.h \
    listar_competencias.h \
    alta_competencia.h \
    res.h \
    tipomodalidad.h \
    tiporesultado.h \
    estado.h \
    mostrar_fixture.h \
    tabla_posiciones.h \
    registrar_usuario.h \
    listar_participante.h \
    gestionar_fixture.h \
    ../../Modules/Excel/generadorexcel.h \
    ../../Modules/Reporte/generadorreporte.h

FORMS    += mainwindow.ui \
    ver_competencia.ui \
    pantalla_usuario.ui \
    modificar_competencia.ui \
    listar_competencias.ui \
    alta_competencia.ui \
    mostrar_fixture.ui \
    tabla_posiciones.ui \
    registrar_usuario.ui \
    listar_participante.ui \
    gestionar_fixture.ui

RESOURCES += \
    res.qrc

include(../../Modules/Excel/qtxlsx/src/xlsx/qtxlsx.pri)
include($$PWD/../../Modules/Reporte/QtRptProject/QtRPT/QtRPT.pri)
