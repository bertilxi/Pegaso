#include "alta_competencia.h"
#include "ui_alta_competencia.h"


alta_competencia::alta_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_competencia)
{
    ui->setupUi(this);
    ui->plainTextEdit->hide();

}

 alta_competencia::alta_competencia(QVector<Deporte*> deportes, QVector<Lugar *> lugares, QVector<TipoModalidad*> modalidades, QWidget *parent):
     QDialog(parent), lugar(lugares), ui(new Ui::alta_competencia)

 {
     ui->setupUi(this);
     ui->plainTextEdit->hide();

     // crear validadores para nombre y para reglamento

     int i;
     for(i=0;i<deportes.size();i++){
         ui->comboBox->addItem(deportes[i]->getNombre());
     }
     for(i=0;i<lugares.size();i++){
         ui->comboBox_3->addItem(lugares[i]->getNombre());
     }
     for(i=0;i<modalidades.size();i++){
         ui->comboBox_2->addItem(modalidades[i]->getNombre());
     }
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
    QString nombreCompetencia = ui->lineEdit->text();
    data.append(nombreCompetencia);
    QString deporte = ui->comboBox->currentText();
    data.append(deporte);
    QString tipoModalidad = ui->comboBox_3->currentText();
    data.append(tipoModalidad);

    if(nombreCompetencia.isEmpty() || deporte.isEmpty() || tipoModalidad.isEmpty()){
        QMessageBox msg;
        msg.setText("Por favor complete todos los datos");
        msg.exec();
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
    if(disp == 0){
        QMessageBox msg;
        msg.setText("Por favor coloque una disponibilidad");
        msg.exec();
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
