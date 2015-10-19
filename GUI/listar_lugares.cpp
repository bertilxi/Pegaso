#include "listar_lugares.h"
#include "ui_listar_lugares.h"
#include "alta_lugar.h"
#include "modificar_lugar.h"
#include "baja_lugar.h"
#include "qpixmap.h"

listar_lugares::listar_lugares(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_lugares)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

listar_lugares::~listar_lugares()
{
    delete ui;
}

void listar_lugares::on_pushButton_6_clicked()
{
    this->close();
}

void listar_lugares::on_pushButton_3_clicked()
{
    alta_lugar * a;
    a = new alta_lugar();
    a->setModal(true);
    a->show();
}

void listar_lugares::on_pushButton_4_clicked()
{
    modificar_lugar * m;
    m = new modificar_lugar();
    m->setModal(true);
    m->show();
}

void listar_lugares::on_pushButton_5_clicked()
{
    baja_lugar * b;
    b = new baja_lugar();
    b->setModal(true);
    b->show();
}
