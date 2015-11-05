#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include "gui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile pegasoDB("pegaso.sql");
    GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos("pegaso.db") ;

//    QVector<Deporte*> deportes;
//    QVector<Pais*> paises;
//    QVector<Estado*> estados;
    QVector<Res*> res;
//    QVector<TipoModalidad*> tiposModalidad;
//    QVector<TipoResultado*> tiposResultado;
//    QVector<Provincia*> provincias;
//    QVector<Localidad*> localidades;
//    QVector<Doc*> documentos;

    QVector<Deporte*>    deportes = gestorBaseDeDatos->getDeportes();

    QVector<Pais*>    paises = gestorBaseDeDatos->getPaises();
    QVector<Estado*>    estados = gestorBaseDeDatos->getEstados();
//    QVector<Modalidad*>    modalidades = gestorBaseDeDatos->getModalidades();
    QVector<TipoModalidad*> tiposModalidad = gestorBaseDeDatos->getTipoModalidades();
//    QVector<Doc*> doc = gestorBaseDeDatos->getDocs();

    GestorUsuarios* gestorUsuarios = new GestorUsuarios(gestorBaseDeDatos);
    GestorPartidos* gestorPartidos = new GestorPartidos(res) ;
    GestorCompetencias* gestorCompetencias = new GestorCompetencias(gestorBaseDeDatos,gestorPartidos,gestorUsuarios,estados);
    GestorLugares* gestorLugares = new GestorLugares(gestorBaseDeDatos);

    GUI * gui = new GUI(gestorBaseDeDatos, gestorCompetencias, gestorLugares, gestorPartidos, gestorUsuarios,
                        deportes, paises, estados, tiposModalidad);

    qDebug()<<gui->getDeportes().size();
    gui->show();

    return a.exec();
}
