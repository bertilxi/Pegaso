#include "listar_competencias.h"
#include "ui_listar_competencias.h"
#include "alta_competencia.h"
#include "ver_competencia.h"
#include "qpixmap.h"

listar_competencias::listar_competencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_competencias)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
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
    alta_competencia * a;
    a = new alta_competencia();
    a->setModal(true);
    a->show();
}

void listar_competencias::on_pushButton_4_clicked()
{
    ver_competencia * v;
    v = new ver_competencia();
    v->setModal(true);
    v->show();
}
