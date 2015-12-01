#include "modificar_competencia.h"
#include "ui_modificar_competencia.h"
#include "qpixmap.h"

modificar_competencia::modificar_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificar_competencia)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

modificar_competencia::~modificar_competencia()
{
    delete ui;
}

void modificar_competencia::on_pushButton_2_clicked()
{
    this->close();
}
