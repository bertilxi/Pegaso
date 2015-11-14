#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T01:04:31
#
#-------------------------------------------------

QT       += core gui sql network

CONFIG += c++11

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
    alta_participante.cpp \
    alta_competencia_liga.cpp \
    alta_competencia_eliminacion.cpp \
    alta_competencia.cpp \
    res.cpp \
    tipomodalidad.cpp \
    tiporesultado.cpp \
    estado.cpp \
    mostrar_fixture.cpp \
    tabla_posiciones.cpp \
    registrar_usuario.cpp

HEADERS  += \
    Atributo.h \
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
    alta_participante.h \
    alta_competencia_liga.h \
    alta_competencia_eliminacion.h \
    alta_competencia.h \
    res.h \
    tipomodalidad.h \
    tiporesultado.h \
    estado.h \
    mostrar_fixture.h \
    tabla_posiciones.h \
    registrar_usuario.h

FORMS    += mainwindow.ui \
    ver_competencia.ui \
    pantalla_usuario.ui \
    modificar_competencia.ui \
    listar_competencias.ui \
    alta_participante.ui \
    alta_competencia.ui \
    mostrar_fixture.ui \
    tabla_posiciones.ui \
    registrar_usuario.ui
