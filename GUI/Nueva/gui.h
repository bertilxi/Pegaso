#ifndef GUI_H
#define GUI_H

#include "mainwindow.h"
#include "GestorBaseDatos.h"
#include "GestorCompetencias.h"
#include "GestorLugares.h"
#include "GestorParticipantes.h"
#include "GestorPartidos.h"
#include "GestorUsuarios.h"

#include "alta_competencia.h"
#include "alta_competencia_eliminacion.h"
#include "alta_competencia_liga.h"
#include "alta_participante.h"

#include "listar_competencias.h"
#include "mainwindow.h"
#include "modificar_competencia.h"
#include "pantalla_usuario.h"
#include "ver_competencia.h"

class GUI
{
private:
    GestorBaseDatos* gestorDB;
    GestorCompetencias* gestorCompetencias;
    GestorLugares* gestorLugares;
    GestorParticipantes* gestorParticipantes;
    GestorPartidos* gestorPartidos;
    GestorUsuarios* gestorUsuarios;


    alta_competencia * altaCompetencia;
    alta_competencia_eliminacion * altaCompetenciaEliminacion;
    alta_competencia_liga * altaCompetenciaLiga;
    alta_participante * altaParticipante;
    listar_competencias * listarCompetencias;
    MainWindow * mainWindow;
    modificar_competencia * modificarCompetencia;
    pantalla_usuario * pantallaUsuario;
    ver_competencia * verCompetencia;

public:
    void show();
    GUI(GestorBaseDatos* gestorDBP, GestorCompetencias* gestorCompetenciasP, GestorLugares* gestorLugaresP, GestorParticipantes* gestorParticipantesP, GestorPartidos* gestorPartidosP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorParticipantes(gestorParticipantesP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP) {}
};

#endif // GUI_H
