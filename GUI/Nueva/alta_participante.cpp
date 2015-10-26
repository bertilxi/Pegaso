#include "alta_participante.h"
#include "ui_alta_participante.h"
#include "qpixmap.h"

alta_participante::alta_participante(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_participante)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

alta_participante::~alta_participante()
{
    delete ui;
}

void alta_participante::on_pushButton_3_clicked()
{
    this->close();
}
