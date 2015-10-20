#include "pantalla_usuario.h"
#include "ui_pantalla_usuario.h"
//#include "modificar_usuario.h"
#include "listar_competencias.h"
//#include "listar_lugares.h"
#include "mainwindow.h"
#include "qpixmap.h"

pantalla_usuario::pantalla_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pantalla_usuario)
{
    ui->setupUi(this);
    //QPixmap pix("/home/fer/Pegaso/Heros128.png");
    //ui->label_logo->setPixmap(pix);
}

pantalla_usuario::~pantalla_usuario()
{
    delete ui;
}

//void pantalla_usuario::on_pushButton_clicked()
//{
//    modificar_usuario * m;
//    m = new modificar_usuario();
//    m->setModal(true);
//    m->show();
//}

void pantalla_usuario::on_pushButton_4_clicked()
{

    MainWindow * m = new MainWindow();
    m->show();
    this->close();
    qDebug()<<"Se abrio la ventana principal y se cerro la pantalla de usuario";
}

void pantalla_usuario::on_pushButton_2_clicked()
{

    listar_competencias * l;
    l= new listar_competencias();
    l->setModal(true);
    l->show();
    qDebug()<<"Ventana de listar competencias abierta";
}

//void pantalla_usuario::on_pushButton_3_clicked()
//{
//    listar_lugares * l;
//    l= new listar_lugares();
//    l->setModal(true);
//    l->show();
//}
