#include "alta_competencia_liga.h"
#include "ui_alta_competencia_liga.h"
#include "qpixmap.h"

alta_competencia_liga::alta_competencia_liga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia_liga)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);
}

alta_competencia_liga::~alta_competencia_liga()
{
    delete ui;
}
