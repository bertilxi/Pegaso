#ifndef REGISTRAR_USUARIO_H
#define REGISTRAR_USUARIO_H

#include <QDialog>
#include "dtos.h"
#include "gui.h"

namespace Ui {
class registrar_usuario;
}

class registrar_usuario : public QDialog
{
    Q_OBJECT

public:

    explicit registrar_usuario(GUI *guiP,QVector<Pais*> paisesP, QWidget *parent = 0);

    ~registrar_usuario();


private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_8_currentIndexChanged(int index);

private:

    Ui::registrar_usuario *ui;

    QVector<Pais *> paises;

    QVector<Provincia *> provincias;

    QVector<Localidad *> localidades;

    GUI * gui;

};

#endif // REGISTRAR_USUARIO_H
