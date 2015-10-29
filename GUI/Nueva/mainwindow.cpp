#include "mainwindow.h"

MainWindow::MainWindow(GUI* guiP, QWidget *parent):
    QMainWindow(parent), gui(guiP), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    gui->handle("main","pantallaUsuario");
    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    gui->handle("cerrar");
    this->close();
    qDebug()<<"se cerro el programa";
}
