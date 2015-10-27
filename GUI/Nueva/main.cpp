#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include "guiwindows.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile pegasoDB("pegaso.sql");
    GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos() ;
    //GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos(pegasoDB) ;
    GestorUsuarios* gestorUsuarios = new GestorUsuarios(NULL);
    GestorPartidos* gestorPartidos = new GestorPartidos(NULL) ;
    GestorCompetencias* gestorCompetencias = new GestorCompetencias(gestorBaseDeDatos,gestorPartidos,gestorUsuarios);
    GestorLugares* gestorLugares = new GestorLugares(NULL);
    GestorParticipantes* gestorParticipantes = new GestorParticipantes(NULL);

    GUI gui(gestorBaseDeDatos, gestorCompetencias, gestorLugares, gestorParticipantes, gestorPartidos, gestorUsuarios);

    gui.show();

    //MainWindow w;


    //w.show();

    return a.exec();
}
