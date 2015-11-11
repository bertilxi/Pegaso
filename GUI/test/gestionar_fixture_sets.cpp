#include "gestionar_fixture_sets.h"
#include "ui_gestionar_fixture_sets.h"
#include "qpixmap.h"

gestionar_fixture_sets::gestionar_fixture_sets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture_sets)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

gestionar_fixture_sets::~gestionar_fixture_sets()
{
    delete ui;
}
