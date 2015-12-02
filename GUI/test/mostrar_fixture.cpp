#include "mostrar_fixture.h"
#include "ui_mostrar_fixture.h"
#include "gestionar_fixture.h"
#include "qpixmap.h"

mostrar_fixture::mostrar_fixture(GUI *guiP, Competencia *comp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mostrar_fixture), competencia(comp), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    qDebug()<< "Tam fixture "<<comp->getPartidos().size();
    for (int i = 0; i < comp->getPartidos().size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(comp->getPartidos()[i]->getFecha())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoA()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoB()->getNombre()));

    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resize(200,450);
}

mostrar_fixture::~mostrar_fixture()
{
    delete ui;
}

void mostrar_fixture::on_pushButton_clicked()
{
    this->close();
}



void mostrar_fixture::on_pushButton_2_clicked()
{
    gui->handleMostrarFixture(this,"gestionarFixture");
}
