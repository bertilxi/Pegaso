#include "tabla_posiciones.h"
#include "ui_tabla_posiciones.h"


tabla_posiciones::tabla_posiciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabla_posiciones)
{
    ui->setupUi(this);
}

tabla_posiciones::tabla_posiciones(QVector<Participante* > participantesP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabla_posiciones)
{
    ui->setupUi(this);
}

tabla_posiciones::~tabla_posiciones()
{
    delete ui;
}

void tabla_posiciones::on_pushButton_3_clicked()
{
    this->close();
}
