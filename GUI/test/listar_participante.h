#ifndef LISTAR_PARTICIPANTE_H
#define LISTAR_PARTICIPANTE_H

#include <QDialog>
#include "Participante.h"
#include "gui.h"

namespace Ui {
class listar_participante;
}

class listar_participante : public QDialog
{
    Q_OBJECT

public:
    listar_participante(GUI* guiP,QVector<Participante*> partP, QWidget *parent = 0);
    ~listar_participante();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::listar_participante *ui;
    QVector<Participante*> participantes;
    GUI* gui;
};

#endif // LISTAR_PARTICIPANTE_H
