#include "popup_alerta.h"
#include "ui_popup_alerta.h"
#include "qpixmap.h"

popup_alerta::popup_alerta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup_alerta)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros-rojo-64.png");
    ui->label_logo->setPixmap(pix);
}

popup_alerta::~popup_alerta()
{
    delete ui;
}
