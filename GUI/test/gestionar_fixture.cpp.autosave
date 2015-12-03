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

    noSePresentoA = false;
    noSePresentoB = false;
    empate = false;

    QString tr = compP->getModalidad()->getTipoRes()->getNombre().toLower();

    if(tr == "resultado final" ){
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(0);
        ui->tabWidget->setTabText(0,"Por Resultado Final");

        ui->checkBox_5->setText("Ganó " + partP->getEquipoA()->getNombre());
        ui->checkBox_6->setText("Ganó " + partP->getEquipoB()->getNombre());

    }
    else if(tr == "por puntos"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setTabText(0,"Por Puntos");

        ui->label_11->setText(partP->getEquipoA()->getNombre());
        ui->label_12->setText(partP->getEquipoB()->getNombre());

        if(competencia->getModalidad()->getTipoMod()->getNombre().toLower() == "liga"){

        }
    }
    else if(tr == "por sets"){
        ui->tabWidget->removeTab(0);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setTabText(0,"Por Sets");

        ui->label_6->setText(partP->getEquipoA()->getNombre());
        ui->label_7->setText(partP->getEquipoB()->getNombre());
        ui->checkBox_10->setText(partP->getEquipoA()->getNombre() + " no se presentó");
        ui->checkBox_11->setText(partP->getEquipoB()->getNombre() + " no se presentó");


        if(compP->getModalidad()->getCant_max_sets() <= 9){


            if(compP->getModalidad()->getCant_max_sets() <= 7){
                ui->lineEdit->hide();
                ui->lineEdit_22->hide();
                ui->lineEdit_16->hide();
                ui->lineEdit_21->hide();
                ui->label_20->hide();
                ui->label_19->hide();
                if(compP->getModalidad()->getCant_max_sets() <= 5){
                    ui->lineEdit_13->hide();
                    ui->lineEdit_20->hide();
                    ui->lineEdit_4->hide();
                    ui->lineEdit_19->hide();
                    ui->label_17->hide();
                    ui->label_18->hide();
                    if(compP->getModalidad()->getCant_max_sets() == 3){
                        ui->lineEdit_14->hide();
                        ui->lineEdit_17->hide();
                        ui->lineEdit_18->hide();
                        ui->lineEdit_3->hide();
                        ui->label_16->hide();
                        ui->label_15->hide();
                    }
                }
            }

        }
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
        ui->checkBox_8->setChecked(false);
        ui->checkBox_9->setChecked(false);
        ui->checkBox_6->setEnabled(false);
        ui->checkBox_5->setEnabled(false);
        ui->checkBox_8->setEnabled(false);
        ui->checkBox_9->setEnabled(false);
    }
    else{

        ui->checkBox_6->setEnabled(true);
        ui->checkBox_5->setEnabled(true);
        ui->checkBox_8->setEnabled(true);
        ui->checkBox_9->setEnabled(true);
    }
}

void gestionar_fixture::on_checkBox_3_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_9->setDisabled(true);
        ui->lineEdit_10->setDisabled(true);
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        noSePresentoA = true;

    }
    else{
        if(!noSePresentoB){
            ui->lineEdit_9->setEnabled(true);
            ui->lineEdit_10->setEnabled(true);

        }
        noSePresentoA = false;
    }
}

void gestionar_fixture::on_checkBox_4_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_10->setDisabled(true);
        ui->lineEdit_9->setDisabled(true);
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        noSePresentoB = true;
    }
    else{
        if(!noSePresentoA){
            ui->lineEdit_10->setEnabled(true);
            ui->lineEdit_9->setEnabled(true);

        }
        noSePresentoB = false;
    }
}

void gestionar_fixture::on_checkBox_8_toggled(bool checked)
{
    if(checked){
        ui->checkBox_5->setDisabled(true);
        ui->checkBox_6->setDisabled(true);
        ui->checkBox_7->setDisabled(true);
        noSePresentoA = true;

    }
    else{
        if(!noSePresentoB){
            ui->checkBox_5->setEnabled(true);
            ui->checkBox_6->setEnabled(true);
            ui->checkBox_7->setEnabled(true);

        }
        noSePresentoA = false;
    }

    qDebug()<<"no A "<<noSePresentoA;
}

void gestionar_fixture::on_checkBox_9_toggled(bool checked)
{
    if(checked){
        ui->checkBox_5->setDisabled(true);
        ui->checkBox_6->setDisabled(true);
        ui->checkBox_7->setDisabled(true);
        noSePresentoB = true;
    }
    else{
        if(!noSePresentoA){
            ui->checkBox_5->setEnabled(true);
            ui->checkBox_6->setEnabled(true);
            ui->checkBox_7->setEnabled(true);

        }
        noSePresentoB = false;
    }
    qDebug()<<"no B "<<noSePresentoB;
}
