#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pantalla_usuario.h"

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//}

MainWindow::MainWindow(QWidget *parent,GestorBaseDatos* gdb, GestorCompetencias* gComp, GestorLugares* gLugares, GestorParticipantes* gParticipantes, GestorPartidos* gPartidos, GestorUsuarios* gUsuarios):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    GestorBaseDatos(gdb),GestorCompetencias(gComp),GestorLugares(gLugares),
    GestorParticipantes(gParticipantes),GestorPartidos(gPartidos),GestorUsuarios(gUsuarios)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int i =0;
    for(;i<3;i++){
        // hacer funcion de validacion para el usuario de la db
        bool valido = true;
        if(valido){
            // conseguir nombre del usuario del gestor de usuarios
            QString user = " ";
            qDebug()<<"Usuario "<<user<<" se ha logeado";

            //hacer auditoria del usuario

            pantalla_usuario * p = new pantalla_usuario();
            p->setModal(true);
            p->show();
            this->close();
            return;
        }
        else
            //mostrar mensaje de error con numero de intentos y posibles errores
            ;
   }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
    qDebug()<<"se cerro el programa";
}
