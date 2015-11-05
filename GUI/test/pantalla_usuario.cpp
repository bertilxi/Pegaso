#include "pantalla_usuario.h"



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

void pantalla_usuario::on_pushButton_4_clicked()
{
    this->close();
}

void pantalla_usuario::on_pushButton_2_clicked()
{
    gui->handlePantallaUsuario(this,QString("listarCompetencias"));

}
