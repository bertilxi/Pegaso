#include "ver_competencia.h"
#include "ui_ver_competencia.h"
#include "qpixmap.h"

ver_competencia::ver_competencia(Competencia *comp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ver_competencia)
{
    ui->setupUi(this);
//    QPixmap pix("/home/fer/Pegaso/Heros64.png");
//    ui->label_logo->setPixmap(pix);

    QString nombre = "Competencia " + comp->getNombre();
    ui->label->setText(nombre);
    ui->label_7->setText(comp->getModalidad()->getTipoMod()->getNombre());
    ui->label_8->setText(comp->getDeporte()->getNombre());
    ui->label_9->setText(comp->getEstado()->getNombre());
    ui->tableWidget->resizeColumnsToContents();

//    comp->getPartidos()[1]->get
    // si la competencia no esta planificada o en disputa no se muestra la tabla
    if (!(comp->getEstado()->getNombre().toLower() == "planificada" || comp->getEstado()->getNombre().toLower() == "en disputa")){
        ui->tableWidget->hide();
        ui->label_6->hide();
    }

}

ver_competencia::~ver_competencia()
{
    delete ui;
}

void ver_competencia::on_pushButton_7_clicked()
{
    this->close();
}
