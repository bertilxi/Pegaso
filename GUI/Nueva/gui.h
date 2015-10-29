#ifndef GUI_H
#define GUI_H

#include "guiwindows.h"

namespace Ui { class MainWindow; }

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
    Ui::MainWindow * mW;
    modificar_competencia * modificarCompetencia;
    pantalla_usuario * pantallaUsuario;
    ver_competencia * verCompetencia;

    handleMain(QString b);
    handlePantallaUsuario(QString b);
    handleListarCompetencias(QString b);
    handleListarLugares(QString b);
    handleAltaCompetencia(QString b);
    handleListarParticipantes(QString b);
    handleVerCompetencia(QString b);
    handleMostrarFixture(QString b);

public:
    void show();
    void handle(char*);
    GUI();
    GUI(GestorBaseDatos* gestorDBP, GestorCompetencias* gestorCompetenciasP, GestorLugares* gestorLugaresP, GestorParticipantes* gestorParticipantesP, GestorPartidos* gestorPartidosP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorParticipantes(gestorParticipantesP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP) {}
};

#endif // GUI_H
