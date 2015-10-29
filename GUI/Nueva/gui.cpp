#include "gui.h"

void GUI::handleMain(QString b)
{
    if (b == "pantallaUsuario")
    {
        /* code */
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

void GUI::handlePantallaUsuario(QString b)
{
    if (b == "listarCompetencia")
    {
        /* code */
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

void GUI::handleListarCompetencias(QString b)
{
    if (b == "altaCompetencia")
    {
        /* code */
    }
    if (b == "verCompetencia")
    {
        /* code */
    }
}

void GUI::handleListarLugares(QString b)
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

void GUI::handleAltaCompetencia(QString b)
{
    if (b == "listarParticipantes")
    {
        /* code */
    }
}

void GUI::handleListarParticipantes(QString b)
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

void GUI::handleVerCompetencia(QString b)
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

void GUI::handleMostrarFixture(QString b)
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

void GUI::handle(QString a,QString b)
{
    
    if (a == "main")
    {
        this->handleMain(QString b);
    }
    else if (a == "pantallaUsuario")
    {
        this->handlePantallaUsuario(QString b);
    }
    else if (a == "listarCompetencias")
    {
        this->handleListarCompetencias(QString b);
    }
    else if (a == "listarLugares")
    {
        this->handleListarLugares(QString b);
    }
    else if (a == "altaCompetencia")
    {
        this->handleAltaCompetencia(QString b);
    }
    else if (a == "listarParticipantes")
    {
        this->handleListarParticipantes(QString b);
    }
    else if (a == "verCompetencia")
    {
        this->handleVerCompetencia(QString b);
    }
    else if (a == "mostrarFixture")
    {
        this->handleMostrarFixture(QString b);
    }
    else if (a == "cerrar")
    {
        /* code */
    }
}
