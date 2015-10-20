#include "listar_participante.h"
#include "ui_listar_participante.h"
#include "alta_participante.h"
#include "modificar_participante.h"
#include "baja_participante.h"
#include "qpixmap.h"

listar_participante::listar_participante(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_participante)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

listar_participante::~listar_participante()
{
    delete ui;
}

void listar_participante::on_pushButton_clicked()
{
    this->close();
}

void listar_participante::on_pushButton_2_clicked()
{
    alta_participante * a;
    a = new alta_participante();
    a->setModal(true);
    a->show();
}

void listar_participante::on_pushButton_3_clicked()
{
    modificar_participante * m;
    m = new modificar_participante();
    m->setModal(true);
    m->show();
}

void listar_participante::on_pushButton_4_clicked()
{
    baja_participante * b;
    b = new baja_participante();
    b->setModal(true);
    b->show();
}
