#include "pantalla_usuario.h"



pantalla_usuario::pantalla_usuario(GUI *guiP, QWidget *parent) :
    QDialog(parent), gui(guiP),
    ui(new Ui::pantalla_usuario)
{
    ui->setupUi(this);

    this->setWindowTitle("Opciones de usuario");

    QPixmap pix(":/images/Heros128.png");
    ui->label_logo->setPixmap(pix);


    ui->pushButton->hide();
    ui->pushButton_3->hide();
}

pantalla_usuario::~pantalla_usuario()
{
    delete ui;
}

void pantalla_usuario::on_pushButton_4_clicked()
{
    gui->handlePantallaUsuario(this,QString("cerrar"));
}

void pantalla_usuario::on_pushButton_2_clicked()
{
    gui->handlePantallaUsuario(this,QString("listarCompetencias"));

}
