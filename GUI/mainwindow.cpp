#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registrar_usuario.h"
#include "ver_todas_competencias.h"
#include "pantalla_usuario.h"
#include "qpixmap.h"
#include "qicon.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros128.png");
    ui->label_logo->setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    registrar_usuario * r;
    r= new registrar_usuario();
    r->setModal(true);
    r->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ver_todas_competencias * v;
    v= new ver_todas_competencias();
    v->setModal(true);
    v->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    pantalla_usuario * p;
    p = new pantalla_usuario();
    p->setModal(true);
    p->show();

    // validacion

    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}
