#include "baja_participante.h"
#include "ui_baja_participante.h"
#include "qpixmap.h"

baja_participante::baja_participante(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baja_participante)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

baja_participante::~baja_participante()
{
    delete ui;
}

void baja_participante::on_pushButton_2_clicked()
{
    this->close();
}
