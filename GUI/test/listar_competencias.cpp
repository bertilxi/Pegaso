#include "listar_competencias.h"


listar_competencias::listar_competencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_competencias)
{
    ui->setupUi(this);
    //QPixmap pix("/home/fer/Pegaso/Heros64.png");
    //ui->label_logo->setPixmap(pix);
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
    alta_competencia * a = new alta_competencia();
    a->setModal(true);
    a->show();
    qDebug()<<"venta de alta competencia abierta";
}

void listar_competencias::on_pushButton_4_clicked()
{
    ver_competencia * v = new ver_competencia();
    v->setModal(true);
    v->show();
}

void listar_competencias::on_pushButton_clicked()
{
    QString usuario =  gestorUsuarios->getActual().getNombre();
    QString usuarioQuery = "select id_usuario from Usuario where nombre = " + usuario;
    int usuarioId = gestorDB->queryId(usuarioQuery);

    QString nombre = ui->lineEdit->text();

    QString deporte = ui->comboBox->currentText();
    QString deportequery = "select id_deporte from Deporte where nombre = " + deporte;
    int deporteId = gestorDB->queryId(queryDeporte);

    QString estado = ui->comboBox_3->currentText();

    QString tipoModalidad = ui->comboBox_2->currentText();
    QString tipoModalidadQuery = "select id_tipo_modalidad from Tipo_modalidad where nombre = " + tipoModalidad;
    int tipoModalidadId = gestorDB->queryId(tipoModalidad);
    DtoGetCompetencia* datos = new DtoGetCompetencia(usuarioId,nombre,deporteId,tipoModalidadId,estado);

    gui->handleFiltrarCompetencias(datos);
}
