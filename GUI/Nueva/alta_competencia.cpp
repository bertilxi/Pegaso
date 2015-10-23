#include "alta_competencia.h"
#include "ui_alta_competencia.h"

alta_competencia::alta_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia)
{
    ui->setupUi(this);

}

alta_competencia::~alta_competencia()
{
    delete ui;
}

void alta_competencia::on_pushButton_2_clicked()
{
    this->close();
}
