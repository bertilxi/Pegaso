#ifndef ALTA_PARTICIPANTE_H
#define ALTA_PARTICIPANTE_H

#include <QDialog>
#include <QFile>
#include "gui.h"
#include <QValidator>
#include <QRegExp>

class GUI;

namespace Ui {
class alta_participante;
}

class alta_participante : public QDialog
{
    Q_OBJECT

public:

    explicit alta_participante(GUI* guiP, QWidget *parent = 0);

    ~alta_participante();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::alta_participante *ui;
    QFile* img;
    GUI* gui;
};



#endif // ALTA_PARTICIPANTE_H
