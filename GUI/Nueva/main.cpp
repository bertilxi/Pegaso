#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GestorBaseDatos gestorBaseDeDatos(0);
    GestorCompetencias gestorCompetencias(0);
    GestorLugares gestorLugares(0);
    GestorParticipantes gestorParticipantes(0);
    GestorPartidos gestorPartidos(0);
    GestorUsuarios gestorUsuarios(0);

    // comentado para pruebas
    // MainWindow pegaso(0,gestorBaseDeDatos,gestorCompetencias,gestorLugares,gestorParticipantes,gestorPartidos,gestorUsuarios);
    MainWindow w;


    w.show();

    return a.exec();
}
