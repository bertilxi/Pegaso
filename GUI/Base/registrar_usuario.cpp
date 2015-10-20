#include "registrar_usuario.h"
#include "ui_registrar_usuario.h"
#include "qpixmap.h"

registrar_usuario::registrar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registrar_usuario)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

registrar_usuario::~registrar_usuario()
{
    delete ui;
}

void registrar_usuario::on_pushButton_2_clicked()
{
     this->close();
}
