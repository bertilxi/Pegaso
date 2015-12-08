#ifndef VER_COMPETENCIA_H
#define VER_COMPETENCIA_H

#include <QDialog>
#include "Competencia.h"
#include "gui.h"

namespace Ui {
class ver_competencia;
}

class ver_competencia : public QDialog
{
    Q_OBJECT

public:

    explicit ver_competencia(GUI* guiP,Competencia *compP, QWidget *parent = 0);

    void actualizar();

    ~ver_competencia();


private slots:

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::ver_competencia *ui;
    GUI* gui;
    Competencia* comp;
};

#endif // VER_COMPETENCIA_H
