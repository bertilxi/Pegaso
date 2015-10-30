#include "gui.h"

void GUI::handleMain(QMainWindow* a, QString b, QVector<QString> datos)
{
    if (b == "pantallaUsuario")
    {
        /*
        Usuario* u = gestorDB->loadUsuario(datos[0]});

        QString passwordDB = u.getPassword();
        */
        if(1/*datos[1] == passwordDB*/){
            pantallaUsuario = new pantalla_usuario();
            a->close();
            pantallaUsuario->show();

        }


    }
    if (b == "registrarUsuario")
    {
        /* code */
    }
    if (b == "listarTodasCompetencias")
    {
        /* code */
    }
}

void GUI::handlePantallaUsuario(QMainWindow *a, QString b)
{
    if (b == "listarCompetencia")
    {
        listarCompetencias = new listar_competencias();
        listarCompetencias->show();
        a->close();
    }
    if (b == "modificarUsuario")
    {
        /* code */
    }
    if (b == "listarLugares")
    {
        /* code */
    }
}

void GUI::handleListarCompetencias(QMainWindow *a, QString b)
{
    if (b == "altaCompetencia")
    {
        altaCompetencia = new alta_competencia();
        altaCompetencia->show();
        a->close();
    }
    if (b == "verCompetencia")
    {
        /* code */
    }
}

void GUI::handleListarLugares(QMainWindow *a, QString b)
{
    if (b == "altaLugar")
    {
        /* code */
    }
    if (b == "bajaLugar")
    {
        /* code */
    }
    if (b == "modificarLugar")
    {
        /* code */
    }
}

void GUI::handleAltaCompetencia(QMainWindow *a, QString b)
{
    if (b == "listarParticipantes")
    {
        listarCompetencias = new listar_competencias();
        listarCompetencias->show();
        a->close();
    }
}

void GUI::handleListarParticipantes(QMainWindow *a, QString b)
{
    if (b == "altaParticipante")
    {
        /* code */
    }
    if (b == "bajaParticipante")
    {
        /* code */
    }
    if (b == "modificarParticipante")
    {
        /* code */
    }
}

void GUI::handleVerCompetencia(QMainWindow *a, QString b)
{
    if (b == "modificarCompetencia")
    {
        /* code */
    }
    if (b == "generarFixture")
    {
        /* code */
    }
    if (b == "bajaCompertencia")
    {
        /* code */
    }
    if (b == "mostrarFixture")
    {
        /* code */
    }
    if (b == "mostrarTablasPosiciones")
    {
        /* code */
    }
}

void GUI::handleMostrarFixture(QMainWindow *a, QString b)
{
    if (b == "generarFixture")
    {
        /* code */
    }
}

void GUI::show()
{
    MainWindow * m = new MainWindow(this,gestorDB);
    m->show();

}

//void GUI::handle(QMainWindow* a, QString b, QVector<QString> args)
//{
    
//    if (a == "main")
//    {
//        this->handleMain(QString b);
//    }
//    else if (a == "pantallaUsuario")
//    {
//        this->handlePantallaUsuario(QString b);
//    }
//    else if (a == "listarCompetencias")
//    {
//        this->handleListarCompetencias(QString b);
//    }
//    else if (a == "listarLugares")
//    {
//        this->handleListarLugares(QString b);
//    }
//    else if (a == "altaCompetencia")
//    {
//        this->handleAltaCompetencia(QString b);
//    }
//    else if (a == "listarParticipantes")
//    {
//        this->handleListarParticipantes(QString b);
//    }
//    else if (a == "verCompetencia")
//    {
//        this->handleVerCompetencia(QString b);
//    }
//    else if (a == "mostrarFixture")
//    {
//        this->handleMostrarFixture(QString b);
//    }
//    else if (a == "cerrar")
//    {
//        /* code */
//    }
//}
