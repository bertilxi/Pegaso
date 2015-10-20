#include "alta_lugar.h"
#include "ui_alta_lugar.h"
#include "qpixmap.h"

alta_lugar::alta_lugar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_lugar)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

alta_lugar::~alta_lugar()
{
    delete ui;
}

void alta_lugar::on_pushButton_2_clicked()
{
    this->close();
}
