#include "gestionar_fixture_puntos.h"
#include "ui_gestionar_fixture_puntos.h"
#include "qpixmap.h"

gestionar_fixture_puntos::gestionar_fixture_puntos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture_puntos)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

gestionar_fixture_puntos::~gestionar_fixture_puntos()
{
    delete ui;
}
