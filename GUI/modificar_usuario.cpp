#include "modificar_usuario.h"
#include "ui_modificar_usuario.h"
#include "qpixmap.h"

modificar_usuario::modificar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificar_usuario)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

modificar_usuario::~modificar_usuario()
{
    delete ui;
}

void modificar_usuario::on_pushButton_2_clicked()
{
    this->close();
}
