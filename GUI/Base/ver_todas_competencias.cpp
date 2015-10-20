#include "ver_todas_competencias.h"
#include "ui_ver_todas_competencias.h"
#include "mostrar_fixture.h"
#include "tabla_posiciones.h"
#include "qpixmap.h"

ver_todas_competencias::ver_todas_competencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ver_todas_competencias)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

ver_todas_competencias::~ver_todas_competencias()
{
    delete ui;
}

void ver_todas_competencias::on_pushButton_2_clicked()
{
    this->close();
}

void ver_todas_competencias::on_pushButton_3_clicked()
{
    mostrar_fixture * m;
    m = new mostrar_fixture();
    m->setModal(true);
    m->show();
}

void ver_todas_competencias::on_pushButton_4_clicked()
{
    tabla_posiciones * t;
    t=new tabla_posiciones();
    t->setModal(true);
    t->show();

}
