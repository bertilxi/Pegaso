#include "gestionar_fixture.h"
#include "ui_gestionar_fixture.h"
#include "qpixmap.h"

gestionar_fixture::gestionar_fixture(GUI *guiP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gestionar_fixture), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":images/Heros64.png");
    ui->label_logo_2->setPixmap(pix);
    ui->label_logo_3->setPixmap(pix);
    ui->label_logo_4->setPixmap(pix);
}

gestionar_fixture::~gestionar_fixture()
{
    delete ui;
}
