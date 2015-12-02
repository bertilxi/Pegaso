#include "gestionar_fixture.h"
#include "ui_gestionar_fixture.h"
#include "qpixmap.h"

gestionar_fixture::gestionar_fixture(Competencia * compP, Partido *partP, GUI *guiP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture), gui(guiP), competencia(compP), partidoGestionado(partP)
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

    QString tr = compP->getModalidad()->getTipoRes()->getNombre().toLower();

    if(tr == "resultado final" ){
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(0);
        ui->tabWidget->setTabText(0,"Por Resultado Final");
    }
    else if(tr == "por puntos"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setTabText(0,"Por Puntos");
        if(competencia->getModalidad()->getTipoMod()->getNombre().toLower() == "liga"){

        }
    }
    else if(tr == "por sets"){
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setTabText(0,"Por Sets");
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
    Partido* p = new Partido();
    Resultado* r = new Resultado();
    QString tr = competencia->getModalidad()->getTipoRes()->getNombre().toLower();
    if(tr == "resultado final" ){
        // gano equipo A
        if(ui->checkBox_5->isChecked()){
            r->setId(-1);
            Res* res = new Res();
            res->setId(1);
            res->setNombre("ganó");
            r->setResultadoA(res);
            Res* res2 = new Res();
            res2->setId(2);
            res2->setNombre("perdió");
            r->setResultadoB(res2);
        }
//        gano Equipo B
        else if (ui->checkBox_6->isChecked()){
            r->setId(-1);
            Res* res = new Res();
            res->setId(1);
            res->setNombre("ganó");
            r->setResultadoB(res);
            Res* res2 = new Res();
            res2->setId(2);
            res2->setNombre("perdió");
            r->setResultadoA(res2);
        }
//        empataron
        else if (ui->checkBox_7->isChecked()){
            r->setId(-1);
            Res* res = new Res();
            res->setId(3);
            res->setNombre("empate");
            r->setResultadoA(res);
            r->setResultadoB(res);
        }
        // equipo A no se presento
        if(ui->checkBox_8->isChecked()){
            r->setId(-1);
            Res* res = new Res();
            res->setId(4);
            res->setNombre("no se presentó");
            r->setResultadoA(res);

        }
        // equipo B no se presento
        if(ui->checkBox_9->isChecked()){
            r->setId(-1);
            Res* res = new Res();
            res->setId(4);
            res->setNombre("no se presentó");
            r->setResultadoB(res);

        }
    }
    else if(tr == "por puntos"){
        int puntosA = ui->lineEdit_9->text().toInt();
        int puntosB = ui->lineEdit_10->text().toInt();

        // si algun equipo esta ausente pero se le coloca puntos dara una alerta de error
        if( (puntosA == 0 && !ui->checkBox_4->isChecked()) || (puntosB == 0 && !ui->checkBox_3->isChecked() )){


        }
        //gano equipo A
        if(puntosA < puntosB){
            r->setId(-1);
            Res* res = new Res();
            res->setId(1);
            res->setNombre("ganó");
            r->setResultadoA(res);
            Res* res2 = new Res();
            res2->setId(2);
            res2->setNombre("perdió");
            r->setResultadoB(res2);
        }
        else{

        }

    }
    else if(tr == "por sets"){

    }


}

void gestionar_fixture::on_checkBox_5_toggled(bool checked)
{
    if(checked){
        ui->checkBox_6->setChecked(false);
        ui->checkBox_7->setChecked(false);
    }
}

void gestionar_fixture::on_checkBox_6_toggled(bool checked)
{
    if(checked){
        ui->checkBox_5->setChecked(false);
        ui->checkBox_7->setChecked(false);
    }
}

void gestionar_fixture::on_checkBox_7_toggled(bool checked)
{
    if(checked){
        ui->checkBox_6->setChecked(false);
        ui->checkBox_5->setChecked(false);
    }
}

void gestionar_fixture::on_checkBox_3_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_9->setDisabled(true);
    }
    else{
        ui->lineEdit_9->setEnabled(true);
    }
}

void gestionar_fixture::on_checkBox_4_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_10->setDisabled(true);
    }
    else{
        ui->lineEdit_10->setEnabled(true);
    }
}
