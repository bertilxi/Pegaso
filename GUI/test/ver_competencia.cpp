#include "ver_competencia.h"
#include "ui_ver_competencia.h"
#include "qpixmap.h"

ver_competencia::ver_competencia(GUI *guiP, Competencia *compP, QWidget *parent) :
    QDialog(parent), gui(guiP),  ui(new Ui::ver_competencia), comp(compP)
{
    ui->setupUi(this);
//    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);

    QString nombre = "Competencia " + compP->getNombre();
    ui->label->setText(nombre);
    ui->label_7->setText(compP->getModalidad()->getTipoMod()->getNombre());
    ui->label_8->setText(compP->getDeporte()->getNombre());
    ui->label_9->setText(compP->getEstado()->getNombre());
    ui->tableWidget->resizeColumnsToContents();

    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);

//    comp->getPartidos()[1]->get
    // si la competencia no esta planificada o en disputa no se muestra la tabla
    if (!(compP->getEstado()->getNombre().toLower() == "planificada" || compP->getEstado()->getNombre().toLower() == "en disputa")){
        ui->tableWidget->hide();
        ui->label_6->hide();
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
    if (gui->handleVerCompetencia(this,QString("generarFixture"),comp)){
        ui->checkBox->setChecked(true);
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        QString error = "";
        msg->setText(error);
        msg->setModal(true);
        msg->show();
    }
}
