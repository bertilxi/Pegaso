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

#include "dtos.h"
#include <QMainWindow>
#include <QDebug>
#include "ui_mainwindow.h"
#include <QCryptographicHash>

namespace Ui {
class MainWindow;
}

class MainWindow;
class pantalla_usuario;
class listar_competencias;

class GUI
{
private:
    GestorBaseDatos* gestorDB;
    GestorCompetencias* gestorCompetencias;
    GestorLugares* gestorLugares;
    GestorPartidos* gestorPartidos;
    GestorUsuarios* gestorUsuarios;


//    alta_competencia * altaCompetencia;
//    alta_competencia_eliminacion * altaCompetenciaEliminacion;
//    alta_competencia_liga * altaCompetenciaLiga;
//    alta_participante * altaParticipante;
//    listar_competencias * listarCompetencias;
//    MainWindow * mW;
//    modificar_competencia * modificarCompetencia;
//    pantalla_usuario * pantallaUsuario;
//    ver_competencia * verCompetencia;



public:
    void show();
    void handleMain(QMainWindow* a,QString b,QVector<QString> datos);
    void handlePantallaUsuario(QDialog* a, QString b);
    void handleListarCompetencias(QDialog* a, QString b);
    void handleListarLugares(QDialog* a , QString b);
    void handleAltaCompetencia(QDialog* a, QString b);
    void handleListarParticipantes(QDialog* a, QString b);
    void handleVerCompetencia(QDialog* a, QString b);
    void handleMostrarFixture(QDialog* a, QString b);
    void handleFiltrarCompetencias(DtoGetCompetencia* datos);
    GUI(GestorBaseDatos* gestorDBP, GestorCompetencias* gestorCompetenciasP, GestorLugares* gestorLugaresP, GestorPartidos* gestorPartidosP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(GUI* guiP , GestorUsuarios *gestorUsuariosP , QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    GUI* gui;
    GestorUsuarios* gestorUsuarios;

};

#endif // GUI_H
