#ifndef MOSTRAR_FIXTURE_H
#define MOSTRAR_FIXTURE_H

#include <QDialog>
#include "Partido.h"
#include "Competencia.h"
#include "gui.h"
#include "ver_competencia.h"

class ver_competencia;
class Partido;

namespace Ui {
    class mostrar_fixture;
}

class mostrar_fixture : public QDialog
{
    Q_OBJECT

public:

    explicit mostrar_fixture(GUI* guiP,Competencia* comp,ver_competencia* vc, QWidget *parent = 0);

    ~mostrar_fixture();

    void actualizarTabla();


private slots:

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:

    Ui::mostrar_fixture *ui;
    GUI* gui;
    Competencia* competencia;
    ver_competencia* verCompetencia;
};

#endif // MOSTRAR_FIXTURE_H
