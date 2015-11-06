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

 alta_competencia::alta_competencia(GUI *guiP, QVector<Deporte*> deportesP, QVector<Lugar *> lugaresP, QVector<TipoModalidad*> modalidadesP, QWidget *parent):
     QDialog(parent), lugar(lugaresP), ui(new Ui::alta_competencia), tiposModalidades(modalidadesP)

 {
     ui->setupUi(this);
     ui->plainTextEdit->hide();
     ui->comboBox->clear();
     ui->comboBox_2->clear();
     ui->comboBox_3->clear();

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
     QRegExp compRegex("[-a-zA-Z0-9_ ]*");
     QValidator* compValidator = new QRegExpValidator(compRegex,this);
     ui->lineEdit->setValidator(compValidator);
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
     ui->lineEdit_5->hide();
     ui->label_5->hide();
     ui->lineEdit_3->hide();
     this->resize(500,600);

     QRegExp numRegex("[0-9]{0,5}");
     QValidator* numValidator = new QRegExpValidator(compRegex,this);
     ui->lineEdit_4->setValidator(numValidator);
     ui->lineEdit_5->setValidator(numValidator);
     ui->lineEdit_2->setValidator(numValidator);

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

    QStringList data;
    QString nombreCompetencia = ui->lineEdit->text().toUpper();
    data.append(nombreCompetencia);
    QString deporte = ui->comboBox->currentText().toUpper();
    data.append(deporte);
    QString tipoModalidad = ui->comboBox_3->currentText().toUpper();
    data.append(tipoModalidad);

    if(nombreCompetencia.isEmpty() || deporte.isEmpty() || tipoModalidad.isEmpty()){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor complete todos los datos");
        msg->setModal(true);
        msg->exec();
    }
    else{


        if(ui->checkBox->isChecked()){
            QString reglamento = ui->plainTextEdit->toPlainText();
            data.append(reglamento);
        }

        gui->handleAltaCompetencia(this,QString("crearCompetencia"),data);
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

    if(nombreCompetencia.isEmpty() || deporte.isEmpty() || tipoModalidad.isEmpty() || disp ==0 ){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor complete los datos y coloque una disponibilidad");
        msg->setModal(true);
        msg->exec();
    }
    else{
        ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(lugar[lugarPos]->getNombre()));
        ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(QString::number(disp)));
        rowCount++;
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

        if(ui->comboBox_4->currentText().toLower() == "por puntos"){
        }
    }
    else if (arg1.toLower() == "eliminación simple"){
        ui->label_6->hide();
        ui->lineEdit_4->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
    }
    else if (arg1.toLower() == "eliminación doble"){
        ui->label_6->hide();
        ui->lineEdit_4->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
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
        ui->label_7->hide();
        ui->lineEdit_5->hide();
    }
    else if(arg1.toLower() == "por puntos"){
        ui->pushButton_11->hide();
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->label_11->hide();
        ui->label_7->show();
        ui->lineEdit_5->show();
        if(ui->comboBox_2->currentText().toLower() == "torneo"){

        }
    }

}

void alta_competencia::on_radioButton_toggled(bool checked)
{
    ui->label_5->show();
    ui->lineEdit_3->show();

}

void alta_competencia::on_radioButton_2_toggled(bool checked)
{
    ui->label_5->hide();
    ui->lineEdit_3->hide();
}
