#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GestorBaseDatos gestorBaseDeDatos;
    GestorCompetencias gestorCompetencias;
    GestorLugares gestorLugares;
    GestorParticipantes gestorParticipantes;
    GestorPartidos gestorPartidos;
    GestorUsuarios gestorUsuarios;

    // comentado para pruebas
    // MainWindow pegaso(0,gestorBaseDeDatos,gestorCompetencias,gestorLugares,gestorParticipantes,gestorPartidos,gestorUsuarios);
    MainWindow w;


    w.show();

    return a.exec();
}
