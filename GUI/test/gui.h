#ifndef GUI_H
#define GUI_H

#include "GestorBaseDatos.h"
#include "GestorCompetencias.h"
#include "GestorLugares.h"
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

namespace Ui { class MainWindow; }

class GUI
{
private:
    GestorBaseDatos* gestorDB;
    GestorCompetencias* gestorCompetencias;
    GestorLugares* gestorLugares;
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



public:
    void show();
    void handleMain(QMainWindow* a,QString b,QVector<QString> datos);
    void handlePantallaUsuario(QMainWindow* a, QString b);
    void handleListarCompetencias(QMainWindow* a, QString b);
    void handleListarLugares(QMainWindow* a , QString b);
    void handleAltaCompetencia(QMainWindow* a, QString b);
    void handleListarParticipantes(QMainWindow* a, QString b);
    void handleVerCompetencia(QMainWindow* a, QString b);
    void handleMostrarFixture(QMainWindow* a, QString b);
    GUI(GestorBaseDatos* gestorDBP, GestorCompetencias* gestorCompetenciasP, GestorLugares* gestorLugaresP, GestorPartidos* gestorPartidosP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP) {}
};

#endif // GUI_H
