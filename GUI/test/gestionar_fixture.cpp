#include "gestionar_fixture.h"
#include "ui_gestionar_fixture.h"
#include "qpixmap.h"

gestionar_fixture::gestionar_fixture(TipoResultado *tr, GUI *guiP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture), gui(guiP), tipoResultado(tr)
{
    ui->setupUi(this);
    QPixmap pix(":images/Heros64.png");
    ui->label_logo_2->setPixmap(pix);
    ui->label_logo_3->setPixmap(pix);
    ui->label_logo_4->setPixmap(pix);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0,"");
    ui->tabWidget->setTabText(1,"");
    ui->tabWidget->setTabText(2,"");

    if(tr->getNombre().toLower() == "resultado final" ){
        ui->tabWidget->setTabText(2,"Por Resultado Final");
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(1);
    }
    else if(tr->getNombre().toLower() == "por puntos"){
        ui->tabWidget->setTabText(0,"Por Puntos");
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(1);
    }
    else if(tr->getNombre().toLower() == "por sets"){
        ui->tabWidget->setTabText(1,"Por Sets");
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(2);
    }

}

gestionar_fixture::~gestionar_fixture()
{
    delete ui;
}

void gestionar_fixture::on_pushButton_2_clicked()
{
    this->close();
}

void gestionar_fixture::on_pushButton_clicked()
{
    QString tr = tipoResultado->getNombre().toLower();
    if(tr == "resultado final" ){

    }
    else if(tr == "por puntos"){

    }
    else if(tr == "por sets"){

    }
}
