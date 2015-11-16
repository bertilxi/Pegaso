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

    ui->comboBox_3->setCurrentIndex(-1);
    ui->pushButton_11->hide();
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_3->hide();
    ui->label_11->hide();
    ui->label_7->hide();
    ui->lineEdit_5->hide();
    QRegExp compRegex("[0-9]{0,5}");
    QValidator* compValidator = new QRegExpValidator(compRegex,this);
    ui->lineEdit_4->setValidator(compValidator);
    ui->lineEdit_5->setValidator(compValidator);


}

alta_competencia_liga::~alta_competencia_liga()
{
    delete ui;
}

void alta_competencia_liga::on_radioButton_toggled(bool checked)
{
    ui->radioButton_2->setChecked(false);
}

void alta_competencia_liga::on_radioButton_2_clicked()
{
    ui->radioButton->setChecked(false);
}

void alta_competencia_liga::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    if(arg1.toLower() == "por sets"){
        ui->label_11->show();
        ui->pushButton_11->show();
        ui->pushButton_10->show();
        ui->pushButton_9->show();
        ui->pushButton_8->show();
        ui->pushButton_3->show();
        ui->label_7->hide();
        ui->lineEdit_5->hide();
    }
    else if(arg1.toLower() == "por puntos"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_3->hide();
        ui->label_11->hide();
        ui->label_7->show();
        ui->lineEdit_5->show();
    }
}
