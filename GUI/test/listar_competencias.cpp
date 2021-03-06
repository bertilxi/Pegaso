#include "listar_competencias.h"


listar_competencias::listar_competencias(GUI *guiP, QVector<Deporte*> deportes, QVector<Estado*> estados, QVector<TipoModalidad*> modalidades, QWidget *parent) :
    QDialog(parent), gui(guiP),
    ui(new Ui::listar_competencias)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setWindowTitle("Listar competencias deportivas");

    QRegExp compRegex("[-a-zA-Z0-9_ ]*");
    QValidator* compValidator = new QRegExpValidator(compRegex,this);
    ui->lineEdit->setValidator(compValidator);


    int i;
    // Carga de comboBox con los datos posibles inyectados desde la base de datos
    for(i=0;i<deportes.size();i++){
        ui->comboBox->addItem(deportes[i]->getNombre());

    }
    for(i=0;i<estados.size();i++){
        ui->comboBox_3->addItem(estados[i]->getNombre());
    }
    for(i=0;i<modalidades.size();i++){
        ui->comboBox_2->addItem(modalidades[i]->getNombre());
    }

    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
    ui->tableWidget->resizeColumnsToContents();

}

listar_competencias::listar_competencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_competencias)
{
    ui->setupUi(this);
    //QPixmap pix("/home/fer/Pegaso/Heros64.png");
    //ui->label_logo->setPixmap(pix);

    // Carga de comboBox con los datos posibles inyectados desde la base de datos
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();

    QRegExp compRegex("[-a-zA-Z0-9_ ]*");
    QValidator* compValidator = new QRegExpValidator(compRegex,this);
    ui->lineEdit->setValidator(compValidator);

    // columnas para nombre, deporte, modalidad, estado
    ui->tableWidget->setColumnCount(4);
//    QHeaderView header;
//    header<<"Nombre"<<"Deporte"<<"Modalidad"<<"Estado";
//    ui->tableWidget->setHorizontalHeader(header);


}

listar_competencias::~listar_competencias()
{
    delete ui;
}

void listar_competencias::on_pushButton_3_clicked()
{
    gui->handleListarCompetencias(this,QString("cerrar"));
}

void listar_competencias::on_pushButton_2_clicked()
{
    gui->handleListarCompetencias(this,"altaCompetencia");
}

void listar_competencias::on_pushButton_4_clicked()
{
    // validar fila seleccionada y tabla no vacia
    // validar pos < comps.size()
    int pos = ui->tableWidget->currentRow() ;

    if(ui->tableWidget->rowCount() > 0 && pos > -1 && pos < comps.size() && comps[pos] != NULL){

        gui->handleListarCompetencias(this,"verCompetencia",comps[pos]);
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor seleccione una competencia");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
}

void listar_competencias::on_pushButton_clicked()
{
    //borramos las competencias cargadas en una búsqueda anterior
    for (int i = 0; i < comps.size(); ++i) {
        delete comps[i];
    }

    QString nombre = ui->lineEdit->text().toUpper();
    QString deporte = ui->comboBox->currentText();
    QString estado = ui->comboBox_3->currentText();
    QString tipoModalidad = ui->comboBox_2->currentText();

    QStringList data;
    data.append(nombre);
    data.append(deporte);
    data.append(estado);
    data.append(tipoModalidad);

    comps = gui->handleFiltrarCompetencias(data);

    mostrarCompetencias();
    ui->tableWidget->resizeColumnsToContents();
    int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    width = width + ui->tableWidget->columnWidth(column);
    width+=15;
    ui->tableWidget->setMinimumWidth(width);
    this->resize(sizeHint().width(),550);

}

void listar_competencias::mostrarCompetencias()
{
//    ui->tableWidget->setRowCount(comps.size());

    ui->tableWidget->setRowCount(0);

    for(int i=0;i<comps.size();i++){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(comps[i]->getNombre()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(comps[i]->getDeporte()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(comps[i]->getModalidad()->getTipoMod()->getNombre()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(comps[i]->getEstado()->getNombre()));

    }
}


void listar_competencias::on_pushButton_5_clicked()
{
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
}
