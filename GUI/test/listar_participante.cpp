#include "listar_participante.h"
#include "ui_listar_participante.h"
#include "alta_participante.h"
#include "qpixmap.h"



listar_participante::listar_participante(GUI *guiP, QVector<Participante *> partP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_participante), participantes(partP), gui(guiP)
{
    ui->setupUi(this);
//    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);

    ui->pushButton_3->hide();
    ui->pushButton_4->hide();

    qDebug()<<"participantes"<< participantes.size();

    for (int i = 0; i < participantes.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantes[i]->getNombre()));
        qDebug()<<"part "<<i<< participantes[i]->getNombre();
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantes[i]->getCorreo()));
    }
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
    gui->handleListarParticipantes(this,QString("altaParticipante"));
}


