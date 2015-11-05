#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include "gui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile pegasoDB("pegaso.sql");
    GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos() ;

    QVector<Deporte*> deportes;
    QVector<Pais*> paises;
    QVector<Estado*> estados;
    QVector<Res*> res;
    QVector<TipoModalidad*> tiposModalidad;
    QVector<TipoResultado*> tiposResultado;
    QVector<Provincia*> provincias;
    QVector<Localidad*> localidades;
    QVector<Doc*> documentos;

    GestorUsuarios* gestorUsuarios = new GestorUsuarios(gestorBaseDeDatos);
    GestorPartidos* gestorPartidos = new GestorPartidos(res) ;
    GestorCompetencias* gestorCompetencias = new GestorCompetencias(gestorBaseDeDatos,gestorPartidos,gestorUsuarios,estados);
    GestorLugares* gestorLugares = new GestorLugares(gestorBaseDeDatos);

    /*
    Cargar Deportes, Localidad, Provincia, Pais
    */
    //    deportes = gestorDB->getDeportes();
    //    paises = gestorDB->getPaises();
    //    estados = gestorDB->getEstados();
    //    modalidades = gestorDB->getModalidades();
    //    tiposModalidad = gestorDB->getTipoModalidades();
//    QVector<Doc*> doc = gestorBaseDeDatos->getDocs();


    GUI gui(gestorBaseDeDatos, gestorCompetencias, gestorLugares, gestorPartidos, gestorUsuarios);

    gui.show();

    //MainWindow w;


    //w.show();

    return a.exec();
}
