#include "ver_competencia.h"
#include "ui_ver_competencia.h"
#include "qpixmap.h"

ver_competencia::ver_competencia(GUI *guiP, Competencia *compP, QWidget *parent) :
    QDialog(parent), gui(guiP),  ui(new Ui::ver_competencia), comp(compP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    this->setWindowTitle("Ver competencias deportivas");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QString nombre = "Competencia " + compP->getNombre();
    ui->label->setText(nombre);
    ui->label_7->setText(compP->getModalidad()->getTipoMod()->getNombre());
    ui->label_8->setText(compP->getDeporte()->getNombre());

    ui->label_9->setText(compP->getEstado()->getNombre());
    ui->tableWidget->resizeColumnsToContents();
    ui->checkBox->setCheckable(false);

    //Si la competencia no está en estado creada, se permite ver el fixture y se tilda el checkbox
    if (compP->getEstado()->getNombre().toLower() != "creada"){
        ui->checkBox->setCheckable(true);
        ui->checkBox->setChecked(true);
        ui->checkBox->setDisabled(true);
        ui->pushButton_4->setEnabled(true);
    }
    else {
        ui->pushButton_4->setDisabled(true);

    }

    if(compP->getEstado()->getNombre().toLower() == "en disputa" || compP->getEstado()->getNombre().toLower() == "finalizada" ){
        ui->pushButton_5->setDisabled(true);
    }
    // si la competencia no esta planificada o en disputa no se muestra la tabla
    if (!(compP->getEstado()->getNombre().toLower() == "planificada" || compP->getEstado()->getNombre().toLower() == "en disputa")){
        ui->tableWidget->hide();
        ui->label_6->hide();
    }
    else{
        QVector<Partido*> proxEnc = comp->getProximosEncuentros() ;
        if(proxEnc.size() == 0){

        }
        else{

            for (int i = 0; i < proxEnc.size(); ++i) {
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(proxEnc[i]->getEquipoA()->getNombre()));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(proxEnc[i]->getEquipoB()->getNombre()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(proxEnc[i]->getFecha())));

            }
            ui->tableWidget->resizeColumnsToContents();
            int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
            for(int column = 0; column < ui->tableWidget->columnCount(); column++)
            width = width + ui->tableWidget->columnWidth(column);
            width+=40;
            ui->tableWidget->setMinimumWidth(width);
            this->resize(sizeHint().width(),573);
        }
    }
}

void ver_competencia::actualizar(Competencia* nuevaComp)
{
    Competencia* compP = comp;
    QString nombre = "Competencia " + compP->getNombre();
    ui->label->setText(nombre);
    ui->label_7->setText(compP->getModalidad()->getTipoMod()->getNombre());
    ui->label_8->setText(compP->getDeporte()->getNombre());

    ui->label_9->setText(compP->getEstado()->getNombre());
    ui->tableWidget->resizeColumnsToContents();

    //Si la competencia no está en estado creada, se permite ver el fixture y se tilda el checkbox
    if (compP->getEstado()->getNombre().toLower() != "creada"){
        ui->checkBox->setCheckable(true);
        ui->checkBox->setChecked(true);
        ui->checkBox->setDisabled(true);
        ui->pushButton_4->setEnabled(true);
    }
    else {
        ui->pushButton_4->setDisabled(true);
        ui->checkBox->setCheckable(false);
    }

    if(compP->getEstado()->getNombre().toLower() == "en disputa" || compP->getEstado()->getNombre().toLower() == "finalizada" ){
        ui->pushButton_5->setDisabled(true);
    }
    // si la competencia no esta planificada o en disputa no se muestra la tabla
    if (!(compP->getEstado()->getNombre().toLower() == "planificada" || compP->getEstado()->getNombre().toLower() == "en disputa")){
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->hide();
        ui->label_6->hide();
        this->resize(495,573);
    }
    else{
        QVector<Partido*> proxEnc = comp->getProximosEncuentros() ;
        if(proxEnc.size() == 0){
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->hide();
            ui->label_6->hide();
            this->resize(495,573);
        }
        else{
            ui->tableWidget->setRowCount(0);
            for (int i = 0; i < proxEnc.size(); ++i) {
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(proxEnc[i]->getEquipoA()->getNombre()));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(proxEnc[i]->getEquipoB()->getNombre()));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(proxEnc[i]->getFecha())));

            }
            ui->tableWidget->resizeColumnsToContents();
            int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
            for(int column = 0; column < ui->tableWidget->columnCount(); column++)
            width = width + ui->tableWidget->columnWidth(column);
            width+=20;
            ui->tableWidget->setMinimumWidth(width);
            this->resize(sizeHint().width(),573);
        }
    }
}

ver_competencia::~ver_competencia()
{
    delete ui;
}

void ver_competencia::on_pushButton_7_clicked() //Salir
{
    delete comp;
    this->close();
}

void ver_competencia::on_pushButton_5_clicked() //Generar fixture
{
    QString error;
    if (gui->handleVerCompetencia(this,QString("generarFixture"), error,comp)){
        //Se coloca el tilde en el checkbox y se permite ver el fixture
        ui->checkBox->setCheckable(true);
        ui->checkBox->setChecked(true);
        ui->checkBox->setDisabled(true);
        ui->pushButton_4->setEnabled(true);

        //También se muestran los próximos encuentros
        ui->tableWidget->show();
        ui->label_6->show();
        QVector<Partido*> proxEnc = comp->getProximosEncuentros();
        ui->tableWidget->setRowCount(0);
        qDebug()<<"proxEnc size = "<<proxEnc.size();
        for (int i = 0; i < proxEnc.size(); ++i) {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(proxEnc[i]->getEquipoA()->getNombre()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(proxEnc[i]->getEquipoB()->getNombre()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(proxEnc[i]->getFecha())));

        }
        ui->tableWidget->resizeColumnsToContents();
        int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
        for(int column = 0; column < ui->tableWidget->columnCount(); column++)
        width = width + ui->tableWidget->columnWidth(column);
        ui->tableWidget->setMinimumWidth(width);
        this->resize(sizeHint().width(),573);

        //Se cambia el estado de la competencia
        ui->label_9->setText(comp->getEstado()->getNombre());
        if(comp->getEstado()->getNombre().toLower() == "en disputa"){

            ui->pushButton_5->setDisabled(true);
        }
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText(error);
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }

}

void ver_competencia::on_pushButton_6_clicked() //Mostrar tabla posiciones
{
    // si la competencia está en disputa o finalizada y es de liga se muestra la tabla, si no, no
    if((comp->getEstado()->getNombre().toLower() == "en disputa" ||
        comp->getEstado()->getNombre().toLower() == "finalizada" ) &&
        comp->getModalidad()->getTipoMod()->getNombre().toLower() == "liga")
    {
        QString error;
        gui->handleVerCompetencia(this,QString("mostrarTablasPosiciones"),error,comp);

    }
    else if(comp->getModalidad()->getTipoMod()->getNombre().toLower() != "liga"){
        QMessageBox* msg = new QMessageBox(this);
        QString error = "No es posible mostrar la tabla de posiciones, la competencia no es de la modalidad de liga";
        msg->setText(error);
        QPixmap icono(":/images/Heros-rojo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        QString error = "No es posible mostrar la tabla de posiciones, la competencia no está en disputa o finalizada";
        msg->setText(error);
        QPixmap icono(":/images/Heros-rojo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
}

void ver_competencia::on_pushButton_4_clicked() //Mostrar fixture
{
    QString error;
    gui->handleVerCompetencia(this,QString("mostrarFixture"),error,comp);
}

void ver_competencia::on_pushButton_clicked() //Listar participantes
{
    QString error;
    gui->handleVerCompetencia(this,QString("listarParticipantes"),error,comp);
}

void ver_competencia::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        ui->pushButton_4->setDisabled(true);
    }
    else if(arg1 == 2){
        ui->pushButton_4->setEnabled(true);
    }
}
