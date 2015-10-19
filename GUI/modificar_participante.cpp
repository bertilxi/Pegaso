#include "modificar_participante.h"
#include "ui_modificar_participante.h"
#include "qpixmap.h"

modificar_participante::modificar_participante(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificar_participante)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

modificar_participante::~modificar_participante()
{
    delete ui;
}

void modificar_participante::on_pushButton_3_clicked()
{
    this->close();
}
