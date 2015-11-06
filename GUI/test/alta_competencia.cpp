#include "alta_competencia.h"
#include "ui_alta_competencia.h"



alta_competencia::alta_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia)
{
    ui->setupUi(this);
    ui->plainTextEdit->hide();
    QRegExp compRegex("[-a-zA-Z0-9_ ]*");
    QValidator* compValidator = new QRegExpValidator(compRegex,this);
    ui->lineEdit->setValidator(compValidator);
    ui->comboBox_2->setCurrentIndex(-1);



}

 alta_competencia::alta_competencia(GUI *guiP, QVector<Deporte*> deportesP, QVector<Lugar *> lugaresP,
    QVector<TipoModalidad*> modalidadesP, QVector<TipoResultado*> resultadosP, QWidget *parent):
     QDialog(parent), lugar(lugaresP), ui(new Ui::alta_competencia), tiposModalidades(modalidadesP), gui(guiP)

 {
     ui->setupUi(this);
     ui->plainTextEdit->hide();
     ui->comboBox->clear();
     ui->comboBox_2->clear();
     ui->comboBox_3->clear();
     ui->comboBox_4->clear();
     ui->radioButton_2->setChecked(true);

     // crear validadores para nombre y para reglamento

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
     QRegExp compRegex("[-a-zA-Z0-9_ ]*");
     QValidator* compValidator = new QRegExpValidator(compRegex,this);
     ui->lineEdit->setValidator(compValidator);

     QRegExp numRegex("[0-9]{0,5}");
     QValidator* numValidator = new QRegExpValidator(numRegex,this);
     ui->lineEdit_4->setValidator(numValidator);
     ui->lineEdit_5->setValidator(numValidator);
     ui->lineEdit_2->setValidator(numValidator);
     ui->lineEdit_3->setValidator(numValidator);

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
     this->resize(500,600);


     maxSet =0;

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
    QString deporte = ui->comboBox->currentText();
    QString tipoModalidad = ui->comboBox_2->currentText();
    QString tipoPuntos = ui->comboBox_4->currentText();

    qDebug()<<nombreCompetencia.isEmpty() << deporte.isEmpty() << tipoModalidad.isEmpty();

    if(nombreCompetencia.isEmpty() || deporte.isEmpty() || tipoModalidad.isEmpty() || ui->tableWidget->item(0,0)->text().isEmpty()){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor complete todos los datos");
        msg->setModal(true);
        msg->exec();
    }
    else{
        Deporte* deporteP = new Deporte();
        deporteP->setNombre(deporte);
        Modalidad* mod = new Modalidad();
        TipoModalidad* tipoMod = new TipoModalidad();
        tipoMod->setNombre(tipoModalidad);
        TipoResultado* tipoRes = new TipoResultado();
        tipoRes->setNombre(tipoPuntos);
        mod->setTipoMod(tipoMod);
        mod->setTipoRes(tipoRes);


        if(tipoPuntos.toLower() == "puntos"){
            mod->setPuntos_presentarse(ui->lineEdit_5->text().toInt());
        }
        else if (tipoPuntos.toLower() == "sets" && maxSet != 0){
            mod->setCant_max_sets(maxSet);
        }

        if(tipoPuntos.toLower() == "torneo"){
            mod->setPuntos_ganar(ui->lineEdit_4->text().toInt());
            mod->setEmpate(conEmpate);
            if(conEmpate){
                mod->setPuntos_empate(ui->lineEdit_3->text().toInt());
            }
        }
        else if(tipoPuntos.toLower() == "eliminación simple" || tipoPuntos.toLower() == "eliminación doble"){

        }

        QVector<int> dispobilidades;
        QVector<Lugar*> lugaresP;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
            Lugar* lAux = new Lugar();
            lAux->setNombre(ui->tableWidget->item(i,0)->text());
            lugaresP.push_back(lAux);
            dispobilidades.push_back( ui->tableWidget->item(i,1)->text().toInt());
        }
        QString reglamento;
        if(ui->checkBox->isChecked()){
            reglamento = ui->plainTextEdit->toPlainText();
        }

        gui->handleAltaCompetencia(this,QString("crearCompetencia"),nombreCompetencia,deporteP,lugaresP,dispobilidades,mod,reglamento);
//        gui->handleAltaCompetencia(this,QString("crearCompetencia"),data);
    }

}

void alta_competencia::on_pushButton_3_clicked()
{
    static int rowCount=0;
    int lugarPos = ui->comboBox_3->currentIndex();
    int disp = ui->lineEdit_2->text().toInt();

    QString nombreCompetencia = ui->lineEdit->text().toUpper();
    QString deporte = ui->comboBox->currentText().toUpper();
    QString tipoModalidad = ui->comboBox_3->currentText().toUpper();

    if(disp == 0 ){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor coloque una disponibilidad");
        msg->setModal(true);
        msg->exec();
    }
    else{
        bool esta = false;
        if(rowCount > 0){
           for (int i = 0; i < rowCount; ++i) {

                if (ui->tableWidget->item(i,0)->text().toLower() == lugar[lugarPos]->getNombre().toLower()){
                    int ant = ui->tableWidget->item(i,1)->text().toInt();
                    ant += disp;
                    qDebug()<<ant;
                    ui->tableWidget->item(i,1)->setText(QString::number(ant));
                    esta = true;
                    break;
                }

            }

           qDebug()<<"esta ?"<<esta;
        }
        if(!esta || rowCount == 0){
            qDebug()<<"esta ??"<<esta;
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(lugar[lugarPos]->getNombre()));
        ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(QString::number(disp)));
        rowCount++;
        qDebug()<<"rowCount "<<rowCount;
        }
    }
}

void alta_competencia::on_pushButton_4_clicked()
{
    int lugarPos = ui->comboBox_3->currentIndex();
    ui->tableWidget->removeRow(lugarPos);
}

void alta_competencia::on_checkBox_stateChanged(int arg1)
{
    qDebug()<<arg1;
    if(arg1 == 2){
        ui->plainTextEdit->show();
    }
    else{
        ui->plainTextEdit->hide();
    }
}

void alta_competencia::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1.toLower() == "torneo"){

        ui->label_6->show();
        ui->lineEdit_4->show();
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
    if(arg1.toLower() == "sets"){
        ui->pushButton_11->show();
        ui->pushButton_10->show();
        ui->pushButton_9->show();
        ui->pushButton_8->show();
        ui->pushButton_5->show();
        ui->label_11->show();
        ui->label_9->show();
        ui->label_7->hide();
        ui->lineEdit_5->hide();
    }
    else if(arg1.toLower() == "puntos"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->label_11->hide();
        ui->label_7->show();
        ui->lineEdit_5->show();
        ui->label_9->hide();
        if(ui->comboBox_2->currentText().toLower() == "torneo"){

            ui->label_6->show();
            ui->lineEdit_4->show();
        }


    }
    else if(arg1.toLower() == "resultado"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->label_11->hide();
        ui->label_6->hide();
        ui->lineEdit_4->hide();
//        ui->radioButton->hide();
//        ui->radioButton_2->hide();
        ui->label_9->hide();
        ui->label_7->hide();
        ui->lineEdit_5->hide();
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
    maxSet = 1;
    if(!ui->pushButton_8->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
    }
//    ui->pushButton_5->setEnabled(true);

}

void alta_competencia::on_pushButton_8_clicked()
{
    maxSet = 3;
    if(!ui->pushButton_9->isEnabled()){
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
    }
    else{
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
    }
}

void alta_competencia::on_pushButton_9_clicked()
{
    maxSet = 5;
    if(!ui->pushButton_10->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
    }
}

void alta_competencia::on_pushButton_10_clicked()
{
    maxSet = 7;
    if(!ui->pushButton_11->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
        ui->pushButton_11->setDisabled(true);
    }
}

void alta_competencia::on_pushButton_11_clicked()
{
    maxSet = 9;
    if(!ui->pushButton_5->isEnabled()){
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);
        ui->pushButton_10->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
    else{
        ui->pushButton_8->setDisabled(true);
        ui->pushButton_9->setDisabled(true);
        ui->pushButton_10->setDisabled(true);
        ui->pushButton_5->setDisabled(true);
    }
}


