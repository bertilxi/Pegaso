#include "alta_competencia_eliminacion.h"
#include "ui_alta_competencia_eliminacion.h"
#include "qpixmap.h"

alta_competencia_eliminacion::alta_competencia_eliminacion(QString modo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia_eliminacion)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);
    ui->horizontalLayout_5->setEnabled(false);
    if (modo.toLower() == "simple"){
        ui->label->setText("Eliminación Simple");
    }
    else{
        ui->label->setText("Eliminación Doble");
    }
}

alta_competencia_eliminacion::~alta_competencia_eliminacion()
{
    delete ui;
}

void alta_competencia_eliminacion::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    if(arg1.toLower() == "por sets"){
        ui->horizontalLayout_5->setEnabled(false);
    }

}
