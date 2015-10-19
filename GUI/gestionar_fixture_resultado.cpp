#include "gestionar_fixture_resultado.h"
#include "ui_gestionar_fixture_resultado.h"
#include "qpixmap.h"

gestionar_fixture_resultado::gestionar_fixture_resultado(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture_resultado)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

gestionar_fixture_resultado::~gestionar_fixture_resultado()
{
    delete ui;
}
