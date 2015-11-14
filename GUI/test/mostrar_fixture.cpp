#include "mostrar_fixture.h"
#include "ui_mostrar_fixture.h"
#include "gestionar_fixture.h"
#include "qpixmap.h"

mostrar_fixture::mostrar_fixture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mostrar_fixture)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

mostrar_fixture::mostrar_fixture(QVector<Partido *> partidosP, QWidget *parent):
    QDialog(parent),
    ui(new Ui::mostrar_fixture)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);

}

mostrar_fixture::~mostrar_fixture()
{
    delete ui;
}

void mostrar_fixture::on_pushButton_clicked()
{
    this->close();
}


