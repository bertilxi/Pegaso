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
    ui->pushButton_11->hide();
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_3->hide();
    ui->label_11->hide();
    ui->comboBox_3->setCurrentIndex(-1);

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
        ui->label_11->show();
        ui->pushButton_11->show();
        ui->pushButton_10->show();
        ui->pushButton_9->show();
        ui->pushButton_8->show();
        ui->pushButton_3->show();
    }
    else if(arg1.toLower() == "por puntos"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_3->hide();
        ui->label_11->hide();
    }

}
