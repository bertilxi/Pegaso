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

    this->setWindowTitle("Gestionar resultados del Fixture");

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

        if(!compP->getModalidad()->getEmpate()){
            ui->checkBox_7->hide();
        }

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
                    if(compP->getModalidad()->getCant_max_sets() <= 3){
                        ui->lineEdit_14->hide();
                        ui->lineEdit_17->hide();
                        ui->lineEdit_18->hide();
                        ui->lineEdit_3->hide();
                        ui->label_16->hide();
                        ui->label_15->hide();
                        if(compP->getModalidad()->getCant_max_sets() == 1 ){
                            ui->lineEdit_15->hide();
                            ui->lineEdit_2->hide();
                            ui->lineEdit_12->hide();
                            ui->lineEdit_5->hide();
                            ui->label_13->hide();
                            ui->label_14->hide();
                        }
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
    Puntos* r = new Puntos();
    Res* res = new Res();
    Res* res2 = new Res();

    QString tr = competencia->getModalidad()->getTipoRes()->getNombre().toLower();
    if(tr == "resultado final" ){

        r->setId(-1);
        // gano equipo A
        if(ui->checkBox_5->isChecked()){
            res->setId(1);
            res->setNombre("ganó");
            r->setResultadoA(res);
            res2->setId(2);
            res2->setNombre("perdió");
            r->setResultadoB(res2);
        }
//        gano Equipo B
        else if (ui->checkBox_6->isChecked()){

            res->setId(1);
            res->setNombre("ganó");
            r->setResultadoB(res);
            res2->setId(2);
            res2->setNombre("perdió");
            r->setResultadoA(res2);
        }
//        empataron
        else if (ui->checkBox_7->isChecked()){

            res->setId(3);
            res->setNombre("empate");
            r->setResultadoA(res);
            r->setResultadoB(res);
        }
        // equipo A no se presento
        if(ui->checkBox_8->isChecked()){

            res->setId(4);
            res->setNombre("no se presentó");
            r->setResultadoA(res);

        }
        // equipo B no se presento
        if(ui->checkBox_9->isChecked()){

            res->setId(4);
            res->setNombre("no se presentó");
            r->setResultadoB(res);

        }
        gui->handleGestionarFixture(this,"",partidoGestionado,r);
    }
    else if(tr == "por puntos"){

        int puntosA = ui->lineEdit_9->text().toInt();
        int puntosB = ui->lineEdit_10->text().toInt();
        // seteamos los puntos de todas formas para ahorrar trabajo
        r->setPuntosA(puntosA);
        r->setPuntosB(puntosB);

        // si algun equipo esta ausente pero se le coloca puntos dara una alerta de error

        if( (ui->lineEdit_9->isEnabled()  && puntosA == 0) ||
            (ui->lineEdit_10->isEnabled() && puntosB == 0 )  ){

            QMessageBox* msg = new QMessageBox(this);
            msg->setText("Coloque los puntos del equipo faltante por favor");
            QPixmap icono(":/images/Heros-amarillo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        // si los puntos son iguales pero no se permite empate
        else if ( (puntosA == puntosB) && !competencia->getModalidad()->getEmpate() ){
            QMessageBox* msg = new QMessageBox(this);
            msg->setText("No se permite empate en esta competencia");
            QPixmap icono(":/images/Heros-rojo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        else{
            r->setId(-1);
            Res* res = new Res();

            if(puntosA == puntosB){
                res->setId(3);
                res->setNombre("empate");
                r->setResultadoA(res);
                r->setResultadoB(res);
            }
            //gano equipo A
            else if(puntosA < puntosB){
                res->setId(1);
                res->setNombre("ganó");
                Res* res2 = new Res();
                res2->setId(2);
                res2->setNombre("perdió");
                r->setResultadoA(res);
                r->setResultadoB(res2);
            }
            // gano equipo B
            else{
                res->setId(1);
                res->setNombre("ganó");
                Res* res2 = new Res();
                res2->setId(2);
                res2->setNombre("perdió");
                r->setResultadoB(res);
                r->setResultadoA(res2);
            }
        }
        gui->handleGestionarFixture(this,"",partidoGestionado,r);
    }
    else if(tr == "por sets"){

        int maxset = competencia->getModalidad()->getCant_max_sets();
        //  bandera para el mensaje de error que indica si falta completar un campo
        bool errFlag = false;
        // bandera para mensaje de error que indica en el caso de que no se permite empate valores iguales
        bool errFlag2 = false;
        // enteros para verificar el empate en caso de que no este permitido
        int sumA = 0 , sumB = 0;
        // preguntamos si la competencia permite o no empate
        bool empate = competencia->getModalidad()->getEmpate();

        // seteamos los valores en -1 para saber que no estan cargados

        int setA1 = -1;
        int setA2 = -1;
        int setA3 = -1;
        int setA4 = -1;
        int setA5 = -1;
        int setA6 = -1;
        int setA7 = -1;
        int setA8 = -1;
        int setA9 = -1;

        int setB1 = -1;
        int setB2 = -1;
        int setB3 = -1;
        int setB4 = -1;
        int setB5 = -1;
        int setB6 = -1;
        int setB7 = -1;
        int setB8 = -1;
        int setB9 = -1;

        // si esta presente se toman los puntos
        if(!ui->checkBox_10->isChecked()){

            setA1 = ui->lineEdit_6->text().toInt();
            setA2 = ui->lineEdit_5->text().toInt();
            setA3 = ui->lineEdit_15->text().toInt();
            setA4 = ui->lineEdit_3->text().toInt();
            setA5 = ui->lineEdit_17->text().toInt();
            setA6 = ui->lineEdit_4->text().toInt();
            setA7 = ui->lineEdit_13->text().toInt();
            setA8 = ui->lineEdit_16->text().toInt();
            setA9 = ui->lineEdit->text().toInt();
        }
        // lo mismo que en el anterior
        if(!ui->checkBox_11->isChecked()){

            setB1 = ui->lineEdit_11->text().toInt();
            setB2 = ui->lineEdit_12->text().toInt();
            setB3 = ui->lineEdit_2->text().toInt();
            setB4 = ui->lineEdit_18->text().toInt();
            setB5 = ui->lineEdit_14->text().toInt();
            setB6 = ui->lineEdit_19->text().toInt();
            setB7 = ui->lineEdit_20->text().toInt();
            setB8 = ui->lineEdit_21->text().toInt();
            setB9 = ui->lineEdit_22->text().toInt();
        }

        // validaciones
        if(maxset >= 1){
            sumA += setA1;
            sumB += setB1;
            if (setA1  == 0 || setB1 == 0 ){

                errFlag = true;
            }
            else if(sumA == sumB){
                errFlag2 = true;
            }
        }
        else if(maxset == 3){
            sumA += setA1 + setA2 + setA3 ;
            sumB += setB1 + setB2 + setB3 ;
                if(setA1  == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0 ){

                    errFlag = true;
                }
                else if (!empate && (sumA == sumB || setA1 == setB1 || setA2 == setB2 || setA3 == setB3)){
                    errFlag2 == true;
                }
        }
        else if(maxset == 5){
            sumA += setA1 + setA2 + setA3 + setA4 + setA5;
            sumB += setB1 + setB2 + setB3 + setB4 + setB5;
                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0
                 setA4 == 0 || setB4 == 0 || setA5 == 0 || setB5 == 0 )
                {
                    errFlag = true;
                }
                else if(!empate && ( sumA == sumB || setA1 == setB1 || setA2 == setB2 || setA3 == setB3 ||
                         setA4 == setB4 || setA5 == setB5))
                {
                    errFlag2 = true;
                }
        }
        else if(maxset == 7){
            sumA += setA1 + setA2 + setA3 + setA4 + setA5 + setA6 + setA7;
            sumB += setB1 + setB2 + setB3 + setB4 + setB5 + setB6 + setB7;
                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0
                 setA4 == 0 || setB4 == 0 || setA5 == 0 || setB5 == 0 || setA6 == 0 || setB6 == 0
                 setA7 == 0 || setB7 == 0 )
                {
                    errFlag = true;
                }
                else if(!empate && (sumA == sumB || setA1 == setB1 || setA2 == setB2 || setA3 == setB3 ||
                         setA4 == setB4 || setA5 == setB5 || setA6 == setB6 || setA7 == setB7))
                {
                    errFlag2 = true;
                }
        }
        else if(maxset == 9){
            sumA += setA1 + setA2 + setA3 + setA4 + setA5 + setA6 + setA7 + setA8 + setA9;
            sumB += setB1 + setB2 + setB3 + setB4 + setB5 + setB6 + setB7 + setB8 + setB9;
                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0
                 setA4 == 0 || setB4 == 0 || setA5 == 0 || setB5 == 0 || setA6 == 0 || setB6 == 0
                 setA7 == 0 || setB7 == 0 || setA8 == 0 || setB8 == 0 || setA9 == 0 || setB9 == 0)
                {
                    errFlag = true;
                }
                else if(!empate && (sumA == sumB || setA1 == setB1 || setA2 == setB2 || setA3 == setB3 ||
                         setA4 == setB4 || setA5 == setB5 || setA6 == setB6 || setA7 == setB7 ||
                         setA8 == setB8 || setA9 == setB9 ))
                {
                    errFlag2 = true;
                }
        }

        if( errFlag ){

            QMessageBox* msg = new QMessageBox(this);
            msg->setText("Coloque los puntos faltantes por favor");
            QPixmap icono(":/images/Heros-amarillo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        else if(errFlag2){

            QMessageBox* msg = new QMessageBox(this);
            msg->setText("No se permite empatar en este competencia");
            QPixmap icono(":/images/Heros-rojo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        else{

            Sets* sets = new Sets();
            QVector<Set*> listaSets;
            sets->setSets(listaSets);
            if(maxset >= 1 ){

                Set* set1 = new Set();
                set1->setNro_set(1);
                set1->setPuntosA(setA1);
                set1->setPuntosB(setB1);
                listaSets.push_back(set1);


                if(maxset >= 3){
                    Set* set2 = new Set();
                    Set* set3 = new Set();
                    set2->setNro_set(2);
                    set2->setPuntosA(setA2);
                    set2->setPuntosB(setB2);
                    set3->setNro_set(3);
                    set3->setPuntosA(setA3);
                    set3->setPuntosB(setB3);
                    listaSets.push_back(set2);
                    listaSets.push_back(set3);

                    if(maxset >= 5){
                        Set* set4 = new Set();
                        Set* set5 = new Set();
                        set4->setNro_set(4);
                        set4->setPuntosA(setA4);
                        set4->setPuntosB(setB4);
                        set5->setNro_set(5);
                        set5->setPuntosA(setA5);
                        set5->setPuntosB(setB5);
                        listaSets.push_back(set4);
                        listaSets.push_back(set5);

                        if(maxset >= 7){
                            Set* set6 = new Set();
                            Set* set7 = new Set();
                            set6->setNro_set(6);
                            set6->setPuntosA(setA6);
                            set6->setPuntosB(setB6);
                            set7->setNro_set(7);
                            set7->setPuntosA(setA7);
                            set7->setPuntosB(setB7);
                            listaSets.push_back(set6);
                            listaSets.push_back(set7);

                            if(maxset == 9){
                                Set* set8 = new Set();
                                Set* set9 = new Set();
                                set8->setNro_set(8);
                                set8->setPuntosA(setA8);
                                set8->setPuntosB(setB8);
                                set9->setNro_set(9);
                                set9->setPuntosA(setA9);
                                set9->setPuntosB(setB9);
                                listaSets.push_back(set8);
                                listaSets.push_back(set9);

                            }
                        }
                    }
                }
            }
            gui->handleGestionarFixture(this,"",partidoGestionado,sets);
        }
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
}
