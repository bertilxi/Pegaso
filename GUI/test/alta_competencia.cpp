#include "alta_competencia.h"
#include "ui_alta_competencia.h"

alta_competencia::alta_competencia(GUI *guiP, QVector<Deporte*> deportesP, QVector<Lugar *> lugaresP,
    QVector<TipoModalidad*> modalidadesP, QVector<TipoResultado*> resultadosP, QWidget *parent):
     QDialog(parent), lugar(lugaresP), ui(new Ui::alta_competencia), tiposModalidades(modalidadesP),
     gui(guiP), deportes(deportesP), modalidades(modalidadesP), tiposResultados(resultadosP)

 {
       ui->setupUi(this);
     QPixmap pix(":/images/Heros64.png");
     ui->label_logo->setPixmap(pix);
     ui->plainTextEdit->hide();
     ui->comboBox->clear();
     ui->comboBox_2->clear();
     ui->comboBox_3->clear();
     ui->comboBox_4->clear();
     ui->radioButton_2->setChecked(true);
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

     this->setWindowTitle("Dar de alta participante");


     rowCount = 0;
     maxSet = -1 ;
     puntoGanado = -1 ;
     puntoPresentarse = -1 ;
     puntoEmpate = -1 ;
     puntoNoPresentarse = -1 ;

     int i;
     for(i=0;i<deportesP.size();i++){
         ui->comboBox->addItem(deportesP[i]->getNombre());
     }
     for(i=0;i<lugaresP.size();i++){
         ui->comboBox_3->addItem(lugaresP[i]->getNombre());
     }
     for(i=0;i<modalidadesP.size();i++){
         ui->comboBox_2->addItem(modalidadesP[i]->getNombre());
     }
     for(i=0;i<resultadosP.size();i++){
         ui->comboBox_4->addItem(resultadosP[i]->getNombre());
     }

     // crear validadores para nombre y para reglamento
     QRegExp compRegex("[-a-zA-Z0-9_ ]*");
     QValidator* compValidator = new QRegExpValidator(compRegex,this);
     ui->lineEdit->setValidator(compValidator);

     QRegExp numRegex("[0-9]{0,5}");
     QValidator* numValidator = new QRegExpValidator(numRegex,this);
     ui->lineEdit_4->setValidator(numValidator);
     ui->lineEdit_5->setValidator(numValidator);
     ui->lineEdit_2->setValidator(numValidator);
     ui->lineEdit_3->setValidator(numValidator);
     ui->lineEdit_6->setValidator(numValidator);

     ui->comboBox->setCurrentIndex(-1);
     ui->comboBox_2->setCurrentIndex(-1);
     ui->comboBox_3->setCurrentIndex(-1);
     ui->comboBox_4->setCurrentIndex(-1);

     ui->pushButton_11->hide();
     ui->pushButton_10->hide();
     ui->pushButton_9->hide();
     ui->pushButton_8->hide();
     ui->pushButton_5->hide();
     ui->label_11->hide();
     ui->label_6->hide();
     ui->lineEdit_4->hide();
     ui->radioButton->hide();
     ui->radioButton_2->hide();
     ui->label_7->hide();
     ui->label_9->hide();
     ui->lineEdit_5->hide();
     ui->label_5->hide();
     ui->lineEdit_3->hide();
     ui->radioButton->setChecked(true);

     ui->lineEdit_6->hide();
     ui->label_12->hide();

     this->resize(300,600);

     maxSet = 0;
     ui->tableWidget->resizeColumnsToContents();

 }

alta_competencia::~alta_competencia()
{
    delete ui;
}

void alta_competencia::on_pushButton_2_clicked()
{
    this->close();
}

void alta_competencia::on_pushButton_clicked()
{

    QString nombreCompetencia = ui->lineEdit->text().toUpper();
    QString deporte = ui->comboBox->currentText().toLower();
    QString tipoModalidad = ui->comboBox_2->currentText().toLower();
    QString tipoPuntos = ui->comboBox_4->currentText().toLower();

    if(nombreCompetencia.isEmpty() || deporte.isEmpty() || tipoModalidad.isEmpty() || ui->tableWidget->item(0,0)->text().isEmpty() ||
            (tipoPuntos.toLower() == "por sets" && maxSet < 0 ) ){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor complete todos los datos");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }

    else if(tipoModalidad.toLower() == "liga" && ui->lineEdit_4->text().toInt() < ui->lineEdit_3->text().toInt()){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Los puntos por partido ganado no deben ser menores que los puntos por empate.");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
    else if(tipoModalidad.toLower() == "liga"  && ui->lineEdit_4->text().toInt() < ui->lineEdit_5->text().toInt()){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Los puntos por partido ganado no deben ser menores que los puntos por presentarse.");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
    else
    {
        Deporte* deporteP = new Deporte();
        deporteP->setNombre(deporte);
        int depId = this->buscarDeporte(deporte);
        deporteP->setId(depId);

        Modalidad* mod = new Modalidad();
        TipoModalidad* tipoMod = new TipoModalidad();
        tipoMod->setNombre(tipoModalidad);
        int tipoModId = this->buscarTipoMod(tipoModalidad);
        tipoMod->setId(tipoModId);

        TipoResultado* tipoRes = new TipoResultado();
        tipoRes->setNombre(tipoPuntos);
        int tipoResId = this->buscarTipoRes(tipoPuntos);
        tipoRes->setId(tipoResId);
        mod->setTipoMod(tipoMod);
        mod->setTipoRes(tipoRes);  

        if(tipoModalidad.toLower() == "eliminación simple" || tipoModalidad.toLower() == "eliminación doble"){

        }
        else if(tipoModalidad.toLower() == "liga"){
            mod->setPuntos_ganar(ui->lineEdit_4->text().toInt());
            mod->setPuntos_presentarse(ui->lineEdit_5->text().toInt());
            mod->setEmpate(conEmpate);

            if(conEmpate){
                mod->setPuntos_empate(ui->lineEdit_3->text().toInt());
            }
            else{
                mod->setPuntos_empate(-1);
            }

            if(tipoPuntos.toLower() == "por puntos"){
                mod->setPuntos_presentarse(ui->lineEdit_5->text().toInt());
                mod->setPuntos_no_presentarse(ui->lineEdit_6->text().toInt());
            }
            else if (tipoPuntos.toLower() == "por sets" && maxSet > 0){
                mod->setCant_max_sets(maxSet);
            }

        }

        QVector<int> dispobilidades;
        QVector<Lugar*> lugaresP;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            Lugar* lAux = new Lugar();
            lAux->setNombre(ui->tableWidget->item(i,0)->text());
            int lugarId = this->buscarLugar(lAux->getNombre());
            lAux->setId(lugarId);
            lugaresP.push_back(lAux);
            dispobilidades.push_back( ui->tableWidget->item(i,1)->text().toInt());
        }
        QString reglamento;
        if(ui->checkBox->isChecked()){
            reglamento = ui->plainTextEdit->toPlainText();
        }

        gui->handleAltaCompetencia(this,QString("crearCompetencia"),nombreCompetencia,deporteP,lugaresP,dispobilidades,mod,reglamento);

    }

}

void alta_competencia::on_pushButton_3_clicked()
{
    int lugarPos = ui->comboBox_3->currentIndex();
    int disp = ui->lineEdit_2->text().toInt();

    QString nombreCompetencia = ui->lineEdit->text().toUpper();
    QString deporte = ui->comboBox->currentText().toUpper();
    QString tipoModalidad = ui->comboBox_3->currentText().toUpper();

    if(disp <= 0 ){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor coloque una disponibilidad");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
    else if( lugarPos < 0){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor seleccione un lugar");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
    else{
        bool esta = false;
        int i;
        if(rowCount > 0){
           for ( i = 0; i < rowCount; ++i) {
                if (ui->tableWidget->item(i,0)->text().toLower() == lugar[lugarPos]->getNombre().toLower()){
                    esta = true;
                    break;
                }
            }          
        }
        if(!esta || rowCount == 0){

        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(lugar[lugarPos]->getNombre()));
        ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(QString::number(disp)));
        rowCount++;

        }
        else{
            ui->tableWidget->item(i,1)->setText(QString::number(disp));
        }

    }
    ui->tableWidget->resizeColumnsToContents();
}

void alta_competencia::on_pushButton_4_clicked()
{
    int lugarPos = ui->comboBox_3->currentIndex();

    ui->tableWidget->removeRow(rowCount);
    if(rowCount>0){
        rowCount--;
    }

}

void alta_competencia::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        ui->plainTextEdit->show();
    }
    else{
        ui->plainTextEdit->hide();
    }
}

void alta_competencia::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1.toLower() == "liga"){

        ui->label_6->show();
        ui->lineEdit_4->show();
        ui->label_7->show();
        ui->lineEdit_5->show();
        ui->radioButton->show();
        ui->radioButton_2->show();

    }
    else if (arg1.toLower() == "eliminación simple"){
        ui->label_6->hide();
        ui->lineEdit_4->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
        ui->radioButton_2->setChecked(true);
        ui->label_5->hide();
        ui->lineEdit_3->hide();

    }
    else if (arg1.toLower() == "eliminación doble"){
        ui->label_6->hide();
        ui->lineEdit_4->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
        ui->radioButton_2->setChecked(true);
        ui->label_5->hide();
        ui->lineEdit_3->hide();
    }

}

void alta_competencia::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    if(arg1.toLower() == "por sets"){
        ui->pushButton_11->show();
        ui->pushButton_10->show();
        ui->pushButton_9->show();
        ui->pushButton_8->show();
        ui->pushButton_5->show();
        ui->label_11->show();
        ui->label_9->show();
        //ui->label_7->hide();
        //ui->lineEdit_5->hide();
        ui->lineEdit_6->hide();
        ui->label_12->hide();
        if(ui->comboBox_2->currentText().toLower() == "liga"){
            ui->label_6->show();
            ui->lineEdit_4->show();
        }
    }
    else if(arg1.toLower() == "por puntos"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->label_11->hide();
        //ui->label_7->hide();
        //ui->lineEdit_5->hide();
        ui->label_9->hide();
        ui->lineEdit_6->show();
        ui->label_12->show();
        if(ui->comboBox_2->currentText().toLower() == "liga"){
            ui->label_6->show();
            ui->lineEdit_4->show();
        }


    }
    else if(arg1.toLower() == "resultado final"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->label_11->hide();
        ui->label_6->hide();
        ui->lineEdit_4->hide();
        ui->label_9->hide();
        //ui->label_7->hide();
        //ui->lineEdit_5->hide();
        ui->lineEdit_6->hide();
        ui->label_12->hide();
        if(ui->comboBox_2->currentText().toLower() == "liga"){
            ui->label_6->show();
            ui->lineEdit_4->show();
        }
    }

}

void alta_competencia::on_radioButton_toggled(bool checked)
{
    ui->label_5->show();
    ui->lineEdit_3->show();
    conEmpate = true;

}

void alta_competencia::on_radioButton_2_toggled(bool checked)
{
    ui->label_5->hide();
    ui->lineEdit_3->hide();
    conEmpate = false;
}

void alta_competencia::on_pushButton_5_clicked()
{

    if(!ui->pushButton_8->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        maxSet = -1;
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
        maxSet = 1;
    }
}

void alta_competencia::on_pushButton_8_clicked()
{

    if(!ui->pushButton_9->isEnabled()){
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        maxSet = -1;
    }
    else{
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
        maxSet = 3;
    }
}

void alta_competencia::on_pushButton_9_clicked()
{

    if(!ui->pushButton_10->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        maxSet = -1;
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
        maxSet = 5;
    }
}

void alta_competencia::on_pushButton_10_clicked()
{

    if(!ui->pushButton_11->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
        maxSet = -1;
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
        maxSet = 7;
    }
}

void alta_competencia::on_pushButton_11_clicked()
{

    if(!ui->pushButton_5->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        maxSet = -1;
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
        maxSet = 9;
    }
}

int alta_competencia::buscarDeporte(QString deporte)
{
    for (int i = 0; i < deportes.size(); ++i) {
        if(deporte.toLower() == deportes[i]->getNombre().toLower())
            return deportes[i]->getId();
    }
    return 0;
}

int alta_competencia::buscarTipoMod(QString modalidad)
{
    for (int i = 0; i < modalidades.size(); ++i) {
        if(modalidad.toLower() == modalidades[i]->getNombre().toLower())
            return modalidades[i]->getId();
    }
    return 0;
}


int alta_competencia::buscarTipoRes(QString resultado)
{
    for (int i = 0; i < tiposResultados.size(); ++i) {
        if(resultado.toLower() == tiposResultados[i]->getNombre().toLower())
            return tiposResultados[i]->getId();
    }
    return 0;
}

int alta_competencia::buscarLugar(QString lugarP)
{
    for (int i = 0; i < lugar.size(); ++i) {
        if(lugarP.toLower() == lugar[i]->getNombre().toLower())
            return lugar[i]->getId();
    }
    return 0;
}
