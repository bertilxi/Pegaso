#include "tabla_posiciones.h"
#include "ui_tabla_posiciones.h"

bool comparePtrParticipante(Participante* a, Participante* b) { return (*a < *b); }

tabla_posiciones::tabla_posiciones(GUI *guiP, Competencia* compP, QWidget *parent, GeneradorExcel *genExcelP, generadorReporte *genRepP) :
    QDialog(parent),
    ui(new Ui::tabla_posiciones), gui(guiP), genExcel(genExcelP), comp(compP), genRep(genRepP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);
    this->setWindowTitle("Tabla de posiciones");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->label_2->setText(comp->getNombre());
    ui->label_4->setText(comp->getModalidad()->getTipoMod()->getNombre());
    ui->label_6->setText(QString::number(comp->getFechaActual()));

    QVector<Participante*> participantesP = comp->getParticipantes();

    qSort(participantesP.begin(),participantesP.end(),comparePtrParticipante);
    comp->setParticipantes(participantesP);
    for (int i = 0; i < participantesP.size(); ++i) {

       ui->tableWidget->insertRow(i);
       int j =0;
       ui->tableWidget->setItem(i,j++,new QTableWidgetItem(participantesP[i]->getNombre()));
       ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPuntos())));
       ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPG())));
       ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPP())));
       if(comp->getModalidad()->getEmpate()){
           ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getPE())));
       }
       else{
           for (int i2 = 0; i2 < ui->tableWidget->columnCount(); ++i2) {
                if(ui->tableWidget->horizontalHeaderItem(i2)->text().toLower() == "pe"){
                    ui->tableWidget->removeColumn(i2);
                }
           }
       }
       if(comp->getModalidad()->getTipoRes()->getNombre().toLower() == "por puntos"){
           ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getTF())));
           ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getTC())));
           ui->tableWidget->setItem(i,j++,new QTableWidgetItem(QString::number(participantesP[i]->getPuntaje()->getDif())));
       }
       else{
           for (int i2 = 0; i2 < ui->tableWidget->columnCount(); ++i2) {
                if(ui->tableWidget->horizontalHeaderItem(i2)->text().toLower() == "dt" ||
                   ui->tableWidget->horizontalHeaderItem(i2)->text().toLower() == "tf" ||
                   ui->tableWidget->horizontalHeaderItem(i2)->text().toLower() == "tc"  )
                {
                    ui->tableWidget->removeColumn(i2);
                }
           }
       }

    }

    ui->tableWidget->resizeColumnsToContents();
//    int ancho = ui->tableWidget->geometry().width()*3.5;
//    qDebug()<<ancho;
//    this->resize(ancho ,500);
    int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    width = width + ui->tableWidget->columnWidth(column);
    ui->tableWidget->setMinimumWidth(width);
    width+=10;
    this->resize(sizeHint().width(),500);
}

tabla_posiciones::~tabla_posiciones()
{
    delete ui;
}

void tabla_posiciones::on_pushButton_3_clicked()
{
    this->close();
}

void tabla_posiciones::on_pushButton_clicked()
{
    genExcel->generarExcel(comp);
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Se ha generado una planilla de cálculo con las posiciones");
    QPixmap icono(":/images/Heros-verde-64.png");
    msg->setIconPixmap(icono);
    msg->setModal(true);
    msg->exec();
}

void tabla_posiciones::on_pushButton_2_clicked()
{
    genRep->generar(comp);
}
