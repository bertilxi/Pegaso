#include "popup_exito.h"
#include "ui_popup_exito.h"
#include "qpixmap.h"

popup_exito::popup_exito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup_exito)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros-verde-64.png");
    ui->label_logo->setPixmap(pix);
}

popup_exito::~popup_exito()
{
    delete ui;
}
