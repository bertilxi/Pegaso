#include "listar_participante.h"
#include "ui_listar_participante.h"
#include "alta_participante.h"
#include "qpixmap.h"



listar_participante::listar_participante(GUI *guiP, QVector<Participante *> partP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_participante), participantes(partP), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    resize(300,400);
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();

    // ocultar alta



    qDebug()<<"participantes"<< participantes.size();
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < participantes.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantes[i]->getNombre()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantes[i]->getCorreo()));
    }
//    ui->tableWidget->resize(500,300);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tab->setVisible(false);
    ui->tabWidget->setTabText(0,"");
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


//    gui->handleListarParticipantes(this,QString("altaParticipante"));
}

