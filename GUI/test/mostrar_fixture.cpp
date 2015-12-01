#include "mostrar_fixture.h"
#include "ui_mostrar_fixture.h"
#include "gestionar_fixture.h"
#include "qpixmap.h"

mostrar_fixture::mostrar_fixture(GUI *guiP, Competencia *comp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mostrar_fixture), competencia(comp), gui(guiP)
{
    ui->setupUi(this);
//    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);

    qDebug()<< "Tam fixture "<<comp->getPartidos().size();
    for (int i = 0; i < comp->getPartidos().size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(comp->getPartidos()[i]->getFecha()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoA()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoB()->getNombre()));

        //  ver tema de los resultados
        //        if(comp->getPartidos()[i]->getEquipoA())


    }
}

mostrar_fixture::~mostrar_fixture()
{
    delete ui;
}

void mostrar_fixture::on_pushButton_clicked()
{
    this->close();
}


