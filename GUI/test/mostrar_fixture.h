#ifndef MOSTRAR_FIXTURE_H
#define MOSTRAR_FIXTURE_H

#include <QDialog>
#include "Partido.h"
#include "Competencia.h"
#include "gui.h"

namespace Ui {
    class mostrar_fixture;
}

class mostrar_fixture : public QDialog
{
    Q_OBJECT

public:

    explicit mostrar_fixture(GUI* guiP,Competencia* comp, QWidget *parent = 0);

    ~mostrar_fixture();


private slots:

    void on_pushButton_clicked();


private:

    Ui::mostrar_fixture *ui;
    GUI* gui;
    Competencia* competencia;
};

#endif // MOSTRAR_FIXTURE_H
