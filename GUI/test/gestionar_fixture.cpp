#include "gestionar_fixture.h"
#include "ui_gestionar_fixture.h"
#include "qpixmap.h"

gestionar_fixture::gestionar_fixture(Competencia * compP, mostrar_fixture *mf, Partido *partP, GUI *guiP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture), gui(guiP), competencia(compP), partidoGestionado(partP), mostrarFixture(mf)
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

    // validadores

    QRegExp numRegex("[0-9]{0,3}");
    QValidator* numValidator = new QRegExpValidator(numRegex,this);

    ui->lineEdit_9->setValidator(numValidator);
    ui->lineEdit_10->setValidator(numValidator);
    ui->lineEdit_6->setValidator(numValidator);
    ui->lineEdit_5->setValidator(numValidator);
    ui->lineEdit_15->setValidator(numValidator);
    ui->lineEdit_3->setValidator(numValidator);
    ui->lineEdit_17->setValidator(numValidator);
    ui->lineEdit_4->setValidator(numValidator);
    ui->lineEdit_13->setValidator(numValidator);
    ui->lineEdit_16->setValidator(numValidator);
    ui->lineEdit->setValidator(numValidator);
    ui->lineEdit_11->setValidator(numValidator);
    ui->lineEdit_12->setValidator(numValidator);
    ui->lineEdit_2->setValidator(numValidator);
    ui->lineEdit_18->setValidator(numValidator);
    ui->lineEdit_14->setValidator(numValidator);
    ui->lineEdit_19->setValidator(numValidator);
    ui->lineEdit_20->setValidator(numValidator);
    ui->lineEdit_21->setValidator(numValidator);
    ui->lineEdit_22->setValidator(numValidator);

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
        if(partidoGestionado->getActual() != NULL)
        {
            // checkbox 5 y 6
            if(partidoGestionado->getActual()->getResultadoA()->getNombre().toLower() == "ganó"){
                ui->checkBox_5->setChecked(true);
            }
            else if(partidoGestionado->getActual()->getResultadoB()->getNombre().toLower() == "ganó"){
                ui->checkBox_6->setChecked(true);
            }
            else if(partidoGestionado->getActual()->getResultadoA()->getNombre().toLower() == "empate"){
                ui->checkBox_7->setChecked(true);
            }
            if(partidoGestionado->getActual()->getResultadoA()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_8->setChecked(true);
            }
            if(partidoGestionado->getActual()->getResultadoB()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_9->setChecked(true);
            }
        }
    }
    else if(tr == "por puntos"){
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setTabText(0,"Por Puntos");

        ui->label_11->setText(partP->getEquipoA()->getNombre());
        ui->label_12->setText(partP->getEquipoB()->getNombre());

        if(partidoGestionado->getActual() != NULL)
        {
            ui->lineEdit_9->setText(QString::number(partidoGestionado->getActual()->getPuntosA()));
            ui->lineEdit_10->setText(QString::number(partidoGestionado->getActual()->getPuntosB()));
            if(partidoGestionado->getActual()->getResultadoA()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_3->setChecked(true);
            }
            if(partidoGestionado->getActual()->getResultadoA()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_4->setChecked(true);
            }
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
        Sets* setsAct = dynamic_cast<Sets *>(partidoGestionado->getActual());

        if(setsAct != NULL){

            if(compP->getModalidad()->getCant_max_sets() >= 1 ){
                ui->lineEdit_6->setText(QString::number(setsAct->getSets()[0]->getPuntosA()));
                ui->lineEdit_11->setText(QString::number(setsAct->getSets()[0]->getPuntosB()));
                if(compP->getModalidad()->getCant_max_sets() >= 3){
                    ui->lineEdit_15->setText(QString::number(setsAct->getSets()[2]->getPuntosA()));
                    ui->lineEdit_2->setText(QString::number(setsAct->getSets()[2]->getPuntosB()));
                    ui->lineEdit_5->setText(QString::number(setsAct->getSets()[1]->getPuntosA()));
                    ui->lineEdit_12->setText(QString::number(setsAct->getSets()[1]->getPuntosB()));
                    if(compP->getModalidad()->getCant_max_sets() >= 5){
                        ui->lineEdit_17->setText(QString::number(setsAct->getSets()[4]->getPuntosA()));
                        ui->lineEdit_14->setText(QString::number(setsAct->getSets()[4]->getPuntosB()));
                        ui->lineEdit_3->setText(QString::number(setsAct->getSets()[3]->getPuntosA()));
                        ui->lineEdit_18->setText(QString::number(setsAct->getSets()[3]->getPuntosB()));
                        if(compP->getModalidad()->getCant_max_sets() >= 7){
                            ui->lineEdit_13->setText(QString::number(setsAct->getSets()[6]->getPuntosA()));
                            ui->lineEdit_20->setText(QString::number(setsAct->getSets()[6]->getPuntosB()));
                            ui->lineEdit_4->setText(QString::number(setsAct->getSets()[5]->getPuntosA()));
                            ui->lineEdit_19->setText(QString::number(setsAct->getSets()[5]->getPuntosB()));
                            if(compP->getModalidad()->getCant_max_sets() == 9){
                                ui->lineEdit->setText(QString::number( setsAct->getSets()[8]->getPuntosA()));
                                ui->lineEdit_22->setText(QString::number(setsAct->getSets()[8]->getPuntosB()));
                                ui->lineEdit_16->setText(QString::number(setsAct->getSets()[7]->getPuntosA()));
                                ui->lineEdit_21->setText(QString::number(setsAct->getSets()[7]->getPuntosB()));
                            }
                        }
                    }
                }
            }

            if(setsAct->getResultadoA()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_10->setChecked(true);
            }
            if(setsAct->getResultadoB()->getNombre().toLower() == "no se presentó"){
                ui->checkBox_11->setChecked(true);
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
    Res* res = new Res();
    Res* res2 = new Res();
    Res* res3 = new Res();
    Res* res4 = new Res();

    QString tr = competencia->getModalidad()->getTipoRes()->getNombre().toLower();
    if(tr == "resultado final" ){
        Resultado* r = new Resultado();
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
            if(ui->checkBox_9->isChecked()){
                r->setResultadoB(res);
            }
            else{
                res2->setId(1);
                res2->setNombre("ganó");
                r->setResultadoB(res2);
            }
        }
        // equipo B no se presento
        if(ui->checkBox_9->isChecked()){
            res->setId(4);
            res->setNombre("no se presentó");
            r->setResultadoB(res);
            if(ui->checkBox_8->isChecked()){
                r->setResultadoA(res);
            }
            else{
                res2->setId(1);
                res2->setNombre("ganó");
                r->setResultadoA(res2);
            }
        }
        gui->handleGestionarFixture(this,"",mostrarFixture,partidoGestionado,r);
    }
    else if(tr == "por puntos"){
        Puntos* r = new Puntos();
        int puntosA = -1;
        int puntosB = -1;

        puntosA = ui->lineEdit_9->text().toInt();
        puntosB = ui->lineEdit_10->text().toInt();
        // seteamos los puntos de todas formas para ahorrar trabajo
        r->setPuntosA(puntosA);
        r->setPuntosB(puntosB);

        // si algun equipo esta ausente pero se le coloca puntos dara una alerta de error

        if( (ui->lineEdit_9->isEnabled()  && puntosA == -1) ||
            (ui->lineEdit_10->isEnabled() && puntosB == -1)  ){

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

            if(puntosA == puntosB){
                res->setId(3);
                res->setNombre("empate");
                r->setResultadoA(res);
                r->setResultadoB(res);
            }
            //gano equipo A
            else if(puntosA > puntosB){
                res->setId(1);
                res->setNombre("ganó");
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
            if(ui->checkBox_3->isChecked()){
                res->setId(4);
                res->setNombre("no se presentó");
                r->setResultadoA(res);
                if(ui->checkBox_4->isChecked()){
                    r->setResultadoB(res);
                }
                else{
                    res2->setId(1);
                    res2->setNombre("ganó");
                    r->setResultadoB(res2);
                }
            }
            if(ui->checkBox_4->isChecked()){
                res->setId(4);
                res->setNombre("no se presentó");
                r->setResultadoB(res);
                if(ui->checkBox_3->isChecked()){
                    r->setResultadoA(res);
                }
                else{
                    res2->setId(1);
                    res2->setNombre("ganó");
                    r->setResultadoA(res2);
                }
            }

            gui->handleGestionarFixture(this,"",mostrarFixture,partidoGestionado,r);
        }
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
        if(!(ui->checkBox_10->isChecked() || ui->checkBox_11->isChecked())){

            if(maxset == 1){
                if(setA1 > setB1) sumA++;
                else if(setA1 < setB1) sumB++;

                if (setA1  == 0 || setB1 == 0 ){

                    errFlag = true;
                }
                else if(sumA == sumB){
                    errFlag2 = true;
                }
            }
            else if(maxset == 3){

                if(setA1 > setB1) sumA++;
                else if(setA1 < setB1) sumB++;
                if(setA2 > setB2) sumA++;
                else if(setA2 < setB2) sumB++;
                if(setA3 > setB3) sumA++;
                else if(setA3 < setB3) sumB++;

                if(setA1  == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0 ){

                    errFlag = true;
                }
                else if (!empate && (sumA == sumB || setA1 == setB1 || setA2 == setB2 || setA3 == setB3)){
                    errFlag2 = true;
                }
            }
            else if(maxset == 5){

                if(setA1 > setB1) sumA++;
                else if(setA1 < setB1) sumB++;
                if(setA2 > setB2) sumA++;
                else if(setA2 < setB2) sumB++;
                if(setA3 > setB3) sumA++;
                else if(setA3 < setB3) sumB++;
                if(setA4 > setB4) sumA++;
                else if(setA4 < setB4) sumB++;
                if(setA5 > setB5) sumA++;
                else if(setA5 < setB5) sumB++;

                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0 ||
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

                if(setA1 > setB1) sumA++;
                else if(setA1 < setB1) sumB++;
                if(setA2 > setB2) sumA++;
                else if(setA2 < setB2) sumB++;
                if(setA3 > setB3) sumA++;
                else if(setA3 < setB3) sumB++;
                if(setA4 > setB4) sumA++;
                else if(setA4 < setB4) sumB++;
                if(setA5 > setB5) sumA++;
                else if(setA5 < setB5) sumB++;
                if(setA6 > setB6) sumA++;
                else if(setA6 < setB6) sumB++;
                if(setA7 > setB7) sumA++;
                else if(setA7 < setB7) sumB++;

                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0 ||
                 setA4 == 0 || setB4 == 0 || setA5 == 0 || setB5 == 0 || setA6 == 0 || setB6 == 0 ||
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

                if(setA1 > setB1) sumA++;
                else if(setA1 < setB1) sumB++;
                if(setA2 > setB2) sumA++;
                else if(setA2 < setB2) sumB++;
                if(setA3 > setB3) sumA++;
                else if(setA3 < setB3) sumB++;
                if(setA4 > setB4) sumA++;
                else if(setA4 < setB4) sumB++;
                if(setA5 > setB5) sumA++;
                else if(setA5 < setB5) sumB++;
                if(setA6 > setB6) sumA++;
                else if(setA6 < setB6) sumB++;
                if(setA7 > setB7) sumA++;
                else if(setA7 < setB7) sumB++;
                if(setA8 > setB8) sumA++;
                else if(setA8 < setB8) sumB++;
                if(setA9 > setB9) sumA++;
                else if(setA9 < setB9) sumB++;

                if(setA1 == 0 || setB1 == 0 || setA2 == 0 || setB2 == 0 || setA3 == 0 || setB3 == 0 ||
                 setA4 == 0 || setB4 == 0 || setA5 == 0 || setB5 == 0 || setA6 == 0 || setB6 == 0 ||
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
        }

        if(errFlag){

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

            res->setId(1);
            res->setNombre("ganó");
            res2->setId(2);
            res2->setNombre("perdió");
            res3->setId(3);
            res3->setNombre("empate");
            res4->setId(4);
            res4->setNombre("no se presentó");

            // gano equipo A
            if(sumA > sumB){
                sets->setResultadoA(res);
                sets->setResultadoB(res2);
            }
            // gano equipo B
            else if(sumA < sumB){
                sets->setResultadoB(res);
                sets->setResultadoA(res2);
            }
            // hay empate, ya esta validado antes, asique no se valida aca
            else if(sumA == sumB){
                sets->setResultadoA(res3);
                sets->setResultadoB(res3);
            }
            // no se presento equipo a
            if(ui->checkBox_10->isChecked()){
                sets->setResultadoA(res4);
                // tampoco se presento equipo b
                if(ui->checkBox_11->isChecked()){
                    sets->setResultadoB(res4);
                }
                // si se presento b, gana b
                else{
                    sets->setResultadoB(res);
                }
            }
            // Se repite el caso para evitar errores, hace lo mismo que if anterior pero cambia al equipo a por el b
            if(ui->checkBox_11->isChecked()){
                sets->setResultadoB(res4);
                if(ui->checkBox_10->isChecked()){
                    sets->setResultadoA(res4);
                }
                else{
                    sets->setResultadoA(res);
                }
            }

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

            sets->setSets(listaSets);
            gui->handleGestionarFixture(this,"",mostrarFixture,partidoGestionado,sets);
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

void gestionar_fixture::on_checkBox_10_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_6->setDisabled(true);
        ui->lineEdit_5->setDisabled(true);
        ui->lineEdit_15->setDisabled(true);
        ui->lineEdit_3->setDisabled(true);
        ui->lineEdit_17->setDisabled(true);
        ui->lineEdit_4->setDisabled(true);
        ui->lineEdit_13->setDisabled(true);
        ui->lineEdit_16->setDisabled(true);
        ui->lineEdit->setDisabled(true);
        ui->lineEdit_11->setDisabled(true);
        ui->lineEdit_12->setDisabled(true);
        ui->lineEdit_2->setDisabled(true);
        ui->lineEdit_18->setDisabled(true);
        ui->lineEdit_14->setDisabled(true);
        ui->lineEdit_19->setDisabled(true);
        ui->lineEdit_20->setDisabled(true);
        ui->lineEdit_21->setDisabled(true);
        ui->lineEdit_22->setDisabled(true);
        ui->lineEdit_6->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_19->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_21->clear();
        ui->lineEdit_22->clear();
        noSePresentoA = true;
    }
    else{
        if(!noSePresentoB){

            ui->lineEdit_6->setEnabled(true);
            ui->lineEdit_5->setEnabled(true);
            ui->lineEdit_15->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_17->setEnabled(true);
            ui->lineEdit_4->setEnabled(true);
            ui->lineEdit_13->setEnabled(true);
            ui->lineEdit_16->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            ui->lineEdit_11->setEnabled(true);
            ui->lineEdit_12->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->lineEdit_18->setEnabled(true);
            ui->lineEdit_14->setEnabled(true);
            ui->lineEdit_19->setEnabled(true);
            ui->lineEdit_20->setEnabled(true);
            ui->lineEdit_21->setEnabled(true);
            ui->lineEdit_22->setEnabled(true);
        }
        noSePresentoA = false;

    }
}

void gestionar_fixture::on_checkBox_11_toggled(bool checked)
{
    if(checked){

        ui->lineEdit_6->setDisabled(true);
        ui->lineEdit_5->setDisabled(true);
        ui->lineEdit_15->setDisabled(true);
        ui->lineEdit_3->setDisabled(true);
        ui->lineEdit_17->setDisabled(true);
        ui->lineEdit_4->setDisabled(true);
        ui->lineEdit_13->setDisabled(true);
        ui->lineEdit_16->setDisabled(true);
        ui->lineEdit->setDisabled(true);
        ui->lineEdit_11->setDisabled(true);
        ui->lineEdit_12->setDisabled(true);
        ui->lineEdit_2->setDisabled(true);
        ui->lineEdit_18->setDisabled(true);
        ui->lineEdit_14->setDisabled(true);
        ui->lineEdit_19->setDisabled(true);
        ui->lineEdit_20->setDisabled(true);
        ui->lineEdit_21->setDisabled(true);
        ui->lineEdit_22->setDisabled(true);
        ui->lineEdit_6->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_19->clear();
        ui->lineEdit_20->clear();
        ui->lineEdit_21->clear();
        ui->lineEdit_22->clear();
        noSePresentoB = true;
    }
    else{
        if(!noSePresentoA){

            ui->lineEdit_6->setEnabled(true);
            ui->lineEdit_5->setEnabled(true);
            ui->lineEdit_15->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_17->setEnabled(true);
            ui->lineEdit_4->setEnabled(true);
            ui->lineEdit_13->setEnabled(true);
            ui->lineEdit_16->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            ui->lineEdit_11->setEnabled(true);
            ui->lineEdit_12->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->lineEdit_18->setEnabled(true);
            ui->lineEdit_14->setEnabled(true);
            ui->lineEdit_19->setEnabled(true);
            ui->lineEdit_20->setEnabled(true);
            ui->lineEdit_21->setEnabled(true);
            ui->lineEdit_22->setEnabled(true);
        }
        noSePresentoB = false;
    }
}

