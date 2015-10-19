#include "modificar_lugar.h"
#include "ui_modificar_lugar.h"
#include "qpixmap.h"

modificar_lugar::modificar_lugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modificar_lugar)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

modificar_lugar::~modificar_lugar()
{
    delete ui;
}

void modificar_lugar::on_pushButton_2_clicked()
{
   this->close();
}
