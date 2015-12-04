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
    explicit gestionar_fixture(Competencia *compP, Partido* partP , GUI* guiP, QWidget *parent = 0);
    ~gestionar_fixture();

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_checkBox_5_toggled(bool checked);

    void on_checkBox_6_toggled(bool checked);

    void on_checkBox_7_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_checkBox_4_toggled(bool checked);

    void on_checkBox_8_toggled(bool checked);

    void on_checkBox_9_toggled(bool checked);

    void on_checkBox_10_toggled(bool checked);

    void on_checkBox_11_toggled(bool checked);

private:
    Ui::gestionar_fixture *ui;
    GUI* gui;
    Competencia* competencia;
    Partido* partidoGestionado;
    bool noSePresentoA;
    bool noSePresentoB;
    bool empate;
};

#endif // GESTIONAR_FIXTURE_H
