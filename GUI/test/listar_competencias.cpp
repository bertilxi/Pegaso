#include "listar_competencias.h"


listar_competencias::listar_competencias(GUI *guiP, QVector<Deporte*> deportes, QVector<Estado*> estados, QVector<TipoModalidad*> modalidades, QWidget *parent) :
    QDialog(parent), gui(guiP),
    ui(new Ui::listar_competencias)
{
    ui->setupUi(this);
    //QPixmap pix("/home/fer/Pegaso/Heros64.png");
    //ui->label_logo->setPixmap(pix);
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();

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
    this->close();
}

void listar_competencias::on_pushButton_2_clicked()
{
    gui->handleListarCompetencias(this,"altaCompetencia");
}

void listar_competencias::on_pushButton_4_clicked()
{
    //validar fila seleccionada y tabla no vacia
    // validar pos < comps.size()

    int pos = ui->tableWidget->currentRow() ;
    gui->handleListarCompetencias(this,"verCompetencia",comps[pos]);
}

void listar_competencias::on_pushButton_clicked()
{
    QString nombre = ui->lineEdit->text().toUpper();
    QString deporte = ui->comboBox->currentText();
    QString estado = ui->comboBox_3->currentText();
    QString tipoModalidad = ui->comboBox_2->currentText();

    qDebug()<< nombre;
    qDebug()<< deporte;
    qDebug()<< estado;
    qDebug()<< tipoModalidad;

    QStringList data;
    data.append(nombre);
    data.append(deporte);
    data.append(estado);
    data.append(tipoModalidad);

   comps = gui->handleFiltrarCompetencias(data);

    mostrarCompetencias();

}

void listar_competencias::mostrarCompetencias()
{
    ui->tableWidget->setRowCount(comps.size());

    int i;
    for(i=0;i<comps.size();i++){

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(comps[i]->getNombre()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(comps[i]->getDeporte()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(comps[i]->getModalidad()->getTipoMod()->getNombre()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(comps[i]->getEstado()->getNombre()));

        qDebug()<<comps[i]->getNombre();
        qDebug()<<comps[i]->getDeporte()->getNombre();
        qDebug()<<comps[i]->getModalidad()->getTipoMod()->getNombre();
        qDebug()<<comps[i]->getEstado()->getNombre();

    }
}

