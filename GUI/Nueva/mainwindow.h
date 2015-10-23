#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "GestorBaseDatos.h"
#include "GestorCompetencias.h"
#include "GestorLugares.h"
#include "GestorParticipantes.h"
#include "GestorPartidos.h"
#include "GestorUsuarios.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget *parent = 0,GestorBaseDatos gdb = 0, GestorCompetencias gComp = 0, GestorLugares gLugares = 0, GestorParticipantes gParticipantes = 0, GestorPartidos gPartidos = 0, GestorUsuarios gUsuarios = 0);
   // MainWindow(QWidget *parent = 0,GestorBaseDatos gdb, GestorCompetencias gComp, GestorLugares gLugares, GestorParticipantes gParticipantes, GestorPartidos gPartidos, GestorUsuarios gUsuarios);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    GestorBaseDatos gestorBaseDeDatos;
    GestorCompetencias gestorCompetencias;
    GestorLugares gestorLugares;
    GestorParticipantes gestorParticipantes;
    GestorPartidos gestorPartidos;
    GestorUsuarios gestorUsuarios;
};

#endif // MAINWINDOW_H
