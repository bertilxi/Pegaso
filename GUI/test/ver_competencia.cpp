#include "ver_competencia.h"
#include "ui_ver_competencia.h"
#include "qpixmap.h"

ver_competencia::ver_competencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ver_competencia)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

ver_competencia::ver_competencia(Competencia *comp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ver_competencia)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

ver_competencia::~ver_competencia()
{
    delete ui;
}

void ver_competencia::on_pushButton_7_clicked()
{
    this->close();
}

void ver_competencia::on_pushButton_2_clicked()
{
    modificar_competencia * m;
    m= new modificar_competencia();
    m->setModal(true);
    m->show();

}

//void ver_competencia::on_pushButton_3_clicked()
//{
//    baja_competencia * b;
//    b = new baja_competencia();
//    b->setModal(true);
//    b->show();
//}

//void ver_competencia::on_pushButton_5_clicked()
//{
//    // algoritmo de generacion de fixture con su correspodiente validacion
//}

//void ver_competencia::on_pushButton_4_clicked()
//{
//    // validacion correspondiente
//    mostrar_fixture * m;
//    m = new mostrar_fixture();
//    m->setModal(true);
//    m->show();

//}

//void ver_competencia::on_pushButton_6_clicked()
//{

//    tabla_posiciones * t;
//    t = new tabla_posiciones();
//    t->setModal(true);
//    t->show();

//}

//void ver_competencia::on_pushButton_clicked()
//{
//    listar_participante * l;
//    l = new listar_participante();
//    l->setModal(true);
//    l->show();
//}



