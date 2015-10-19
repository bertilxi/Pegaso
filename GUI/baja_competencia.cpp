#include "baja_competencia.h"
#include "ui_baja_competencia.h"
#include "qpixmap.h"

baja_competencia::baja_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baja_competencia)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

baja_competencia::~baja_competencia()
{
    delete ui;
}

void baja_competencia::on_pushButton_2_clicked()
{
    this->close();
}
