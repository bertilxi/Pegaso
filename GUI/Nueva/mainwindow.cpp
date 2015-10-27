#include "mainwindow.h"


MainWindow::MainWindow(GUI guiP, GestorBaseDatos* gestorDBP, QWidget *parent):
    QMainWindow(parent), gui(guiP), gestorDB(gestorDBP), ui(new Ui::MainWindow)
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
