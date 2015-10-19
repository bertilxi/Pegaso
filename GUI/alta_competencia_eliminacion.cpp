#include "alta_competencia_eliminacion.h"
#include "ui_alta_competencia_eliminacion.h"
#include "qpixmap.h"

alta_competencia_eliminacion::alta_competencia_eliminacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia_eliminacion)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

alta_competencia_eliminacion::~alta_competencia_eliminacion()
{
    delete ui;
}
