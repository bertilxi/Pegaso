#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include "gui.h"
#include <QtSql/QSqlQuery>

/**
 *  @mainpage Proyecto Pegaso.
 *
 *  @brief
 *
 *
 *
 *
 *  @author Berti Fernando
 *  @author Campodonico Daniel
 *  @author Rico Andres
 */

int main(int argc, char *argv[])
{
    QApplication* a = new QApplication(argc, argv);
    a->setQuitOnLastWindowClosed(false);
    /**
     * creamos el gestor de la base de datos y
     * lo inicializamos con el archivo de la base de datos
     */

    GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos() ;

    /**
     * Cargamos todos los objetos que sean necesarios para el sistema
     * y que sean comunes para todos los usuarios, competencias, etc
     * como los deportes, tipo de resultados, paises, etc
     */
    QVector<Deporte*>    deportes = gestorBaseDeDatos->getDeportes();    
    QVector<Res*> res;    
    QVector<Pais*>    paises = gestorBaseDeDatos->getPaises();    
    QVector<Estado*>    estados = gestorBaseDeDatos->getEstados();
    QVector<TipoModalidad*> tiposModalidad = gestorBaseDeDatos->getTipoModalidades();

    /* Creamos los gestores del sistema y los inyectamos con sus respectivas dependencias,
     * siendo que estos gestores van a ser singletons ( concepto matematico, no patron de diseño)
     * No se inyectara nada que no sea realmente necesario a los gestores.
     */

    GestorUsuarios* gestorUsuarios = new GestorUsuarios(gestorBaseDeDatos);
    GestorPartidos* gestorPartidos = new GestorPartidos(res) ;
    GestorCompetencias* gestorCompetencias = new GestorCompetencias(
                gestorBaseDeDatos, gestorPartidos, gestorUsuarios,estados);
    GestorLugares* gestorLugares = new GestorLugares(gestorBaseDeDatos, gestorUsuarios);

    /**
     * Creamos la interfaz que actuara como mediador entre las ventanas graficas y los gestores,
     * unificando el control de las ventanas graficas y los gestores .
     * Se lo inyecta con todos los gestores y datos cargados de la base de datos,
     * ya que los va a necesitar para gestionar todo.
     */
    GUI * gui = new GUI(a,gestorBaseDeDatos, gestorCompetencias, gestorLugares, gestorPartidos, gestorUsuarios,
                        deportes, paises, estados, tiposModalidad);
    // mostramos el programa.
    gui->show();

    return a->exec();
}
