#include "baja_lugar.h"
#include "ui_baja_lugar.h"
#include "qpixmap.h"

baja_lugar::baja_lugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::baja_lugar)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

baja_lugar::~baja_lugar()
{
    delete ui;
}

void baja_lugar::on_pushButton_2_clicked()
{
    this->close();
}
