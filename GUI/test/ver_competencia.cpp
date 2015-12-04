#include "ver_competencia.h"
#include "ui_ver_competencia.h"
#include "qpixmap.h"

ver_competencia::ver_competencia(GUI *guiP, Competencia *compP, QWidget *parent) :
    QDialog(parent), gui(guiP),  ui(new Ui::ver_competencia), comp(compP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    this->setWindowTitle("Ver competencias deportivas");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QString nombre = "Competencia " + compP->getNombre();
    ui->label->setText(nombre);
    ui->label_7->setText(compP->getModalidad()->getTipoMod()->getNombre());
    ui->label_8->setText(compP->getDeporte()->getNombre());
    ui->label_9->setText(compP->getEstado()->getNombre());
    ui->tableWidget->resizeColumnsToContents();

    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->setDisabled(true);


    // si la competencia no esta planificada o en disputa no se muestra la tabla
    if (!(compP->getEstado()->getNombre().toLower() == "planificada" || compP->getEstado()->getNombre().toLower() == "en disputa")){
        ui->tableWidget->hide();
        ui->label_6->hide();
    }
    else{
        QVector<Partido*> proxEnc = comp->getProximosEncuentros() ;
        if(proxEnc.size() == 0){

        }
        else{

            for (int i = 0; i < proxEnc.size(); ++i) {
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(proxEnc[i]->getEquipoA()->getNombre()));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(proxEnc[i]->getEquipoB()->getNombre()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(proxEnc[i]->getFecha())));

            }
        }
    }
}

ver_competencia::~ver_competencia()
{
    delete ui;
}

void ver_competencia::on_pushButton_7_clicked()
{
    this->close();
}

void ver_competencia::on_pushButton_5_clicked()
{
    QString error;
    if (gui->handleVerCompetencia(this,QString("generarFixture"),error,comp)){
        ui->checkBox->setCheckable(true);
        ui->checkBox->setChecked(true);
        ui->checkBox->setDisabled(true);
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText(error);
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
}

void ver_competencia::on_pushButton_6_clicked()
{
    // si la competencia esta en disputa o finalizada y es de liga se muestra el fixture, sino no
    if((comp->getEstado()->getNombre().toLower() == "en disputa" ||
        comp->getEstado()->getNombre().toLower() == "finalizada" ) &&
        comp->getModalidad()->getTipoMod()->getNombre().toLower() == "liga")
    {
        gui->handleVerCompetencia(this,QString("mostrarTablasPosiciones"),"",comp);

    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        QString error = "No es posible mostrar la tabla de posiciones";
        msg->setText(error);
        QPixmap icono(":/images/Heros-rojo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
}

void ver_competencia::on_pushButton_4_clicked()
{
    gui->handleVerCompetencia(this,QString("mostrarFixture"),"",comp);
}

void ver_competencia::on_pushButton_clicked()
{
    gui->handleVerCompetencia(this,QString("listarParticipantes"),"",comp);
}

void ver_competencia::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->pushButton_4->setDisabled(true);
    }
    else if(arg1 == 2){
        ui->pushButton_4->setEnabled(true);
    }
}
