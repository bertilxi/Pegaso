#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include "gui.h"
#include <QtSql/QSqlQuery>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile pegasoDB("pegaso.sql");
    GestorBaseDatos * gestorBaseDeDatos = new GestorBaseDatos("pegaso.db") ;

//    QByteArray passwordHash = QCryptographicHash::hash(QByteArray::fromStdString("root1234"),QCryptographicHash::Sha256);

//    QString str = "UPDATE Usuario SET password = ? ";

//    QSqlQuery query;
//    query.prepare(str);
//    query.addBindValue(passwordHash);

//    query.exec();


//    QVector<Deporte*> deportes;
//    QVector<Pais*> paises;
//    QVector<Estado*> estados;
//    QVector<TipoModalidad*> tiposModalidad;
//    QVector<TipoResultado*> tiposResultado;
//    QVector<Provincia*> provincias;
//    QVector<Localidad*> localidades;
//    QVector<Doc*> documentos;

//    QVector<Doc*> doc = gestorBaseDeDatos->getDocs();
    QVector<Modalidad*>    modalidades = gestorBaseDeDatos->getModalidades();

    QVector<Deporte*>    deportes = gestorBaseDeDatos->getDeportes();
    QVector<Res*> res;
    QVector<Pais*>    paises = gestorBaseDeDatos->getPaises();
    QVector<Estado*>    estados = gestorBaseDeDatos->getEstados();
    QVector<TipoModalidad*> tiposModalidad = gestorBaseDeDatos->getTipoModalidades();


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
