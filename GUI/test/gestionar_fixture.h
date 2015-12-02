#ifndef GESTIONAR_FIXTURE_H
#define GESTIONAR_FIXTURE_H

#include <QDialog>
#include "gui.h"
#include "tiporesultado.h"

namespace Ui {
class gestionar_fixture;
}

class gestionar_fixture : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture(Modalidad *mod, GUI* guiP, QWidget *parent = 0);
    ~gestionar_fixture();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::gestionar_fixture *ui;
    GUI* gui;
    Modalidad* modalidad;
};

#endif // GESTIONAR_FIXTURE_H
