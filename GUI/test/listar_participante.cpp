#include "listar_participante.h"
#include "ui_listar_participante.h"
#include "alta_participante.h"
#include "qpixmap.h"



listar_participante::listar_participante(GUI *guiP, Competencia *compP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_participante), competencia(compP), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    resize(300,400);
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->label_2->setText(compP->getNombre());

    participantes = compP->getParticipantes();
    // ocultar alta

    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < participantes.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantes[i]->getNombre()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantes[i]->getCorreo()));
    }
//    ui->tableWidget->resize(500,300);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0,"Participantes");
    ui->tabWidget->setTabText(1,"");
//    ui->tabWidget->setTabEnabled(0,false);
//    ui->tabWidget->setTabEnabled(1,false);

}

listar_participante::~listar_participante()
{
    delete ui;
}

void listar_participante::on_pushButton_clicked()
{
    this->close();
}

void listar_participante::on_pushButton_2_clicked()
{
    int actual = ui->tabWidget->currentIndex();

    if(actual == 0){

        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabText(0,"");
        ui->tabWidget->setTabText(1,"Nuevo Participante");
    }
    else{

    }

//    gui->handleListarParticipantes(this,QString("altaParticipante"));
}


void listar_participante::on_pushButton_7_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0,"Participantes");
    ui->tabWidget->setTabText(1,"");
}

void listar_participante::on_tabWidget_currentChanged(int index)
{
    if(index == 0){
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->setTabText(0,"Participantes");
        ui->tabWidget->setTabText(1,"");
    }
}

void listar_participante::on_pushButton_8_clicked()
{
    QString email = ui->lineEdit_2->text();
    QString nombre = ui->lineEdit->text();

    // tomar ruta de imagen

    QString imgUrl = "";
    QVector<Participante*> participantesActualizados = gui->handleAltaParticipante(this,nombre,email,imgUrl);
//    participantes =

    qDebug()<<participantesActualizados.size() ;
    if(participantesActualizados.size() != 0){

        ui->tableWidget->setRowCount(0);
        for (int i = 0; i < participantesActualizados.size(); ++i) {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantesActualizados[i]->getNombre()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantesActualizados[i]->getCorreo()));
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        participantes = participantesActualizados;
        ui->tableWidget->resizeColumnsToContents();
        this->on_pushButton_7_clicked();
    }

}
