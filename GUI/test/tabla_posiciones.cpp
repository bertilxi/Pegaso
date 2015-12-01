#include "tabla_posiciones.h"
#include "ui_tabla_posiciones.h"

tabla_posiciones::tabla_posiciones(GUI *guiP, QVector<Participante* > participantesP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabla_posiciones), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    for (int i = 0; i < participantesP.size(); ++i) {

        qDebug()<<"mis puntos "<<i;
       qDebug()<<participantesP[i]->getPuntaje()->getPuntos();

       ui->tableWidget->insertRow(i);

       ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantesP[i]->getNombre()));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPuntos())));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPG())));
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPE())));
       ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPP())));
       ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getTF())));
       ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getTC())));
       ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getDif())));

    }

}

tabla_posiciones::~tabla_posiciones()
{
    delete ui;
}

void tabla_posiciones::on_pushButton_3_clicked()
{
    this->close();
}
