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
    GestorUsuarios* gestorUsuarios = new GestorUsuarios(gestorBaseDeDatos);
    GestorPartidos* gestorPartidos = new GestorPartidos(gestorBaseDeDatos) ;
    GestorCompetencias* gestorCompetencias = new GestorCompetencias(gestorBaseDeDatos,gestorPartidos,gestorUsuarios);
    GestorLugares* gestorLugares = new GestorLugares(gestorBaseDeDatos);
    GestorParticipantes* gestorParticipantes = new GestorParticipantes(gestorBaseDeDatos);

    GUI gui(gestorBaseDeDatos, gestorCompetencias, gestorLugares, gestorParticipantes, gestorPartidos, gestorUsuarios);

    gui.show();

    //MainWindow w;


    //w.show();

    return a.exec();
}
