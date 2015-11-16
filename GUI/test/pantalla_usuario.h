#ifndef PANTALLA_USUARIO_H
#define PANTALLA_USUARIO_H

#include <QDialog>
#include "ui_pantalla_usuario.h"
#include "qpixmap.h"
#include "gui.h"

namespace Ui {
    class pantalla_usuario;
}

class GUI;

class pantalla_usuario : public QDialog
{
    Q_OBJECT

public:

    explicit pantalla_usuario(GUI* guiP, QWidget *parent = 0);

    ~pantalla_usuario();


private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();


private:

    GUI* gui;

    Ui::pantalla_usuario *ui;

};

#endif // PANTALLA_USUARIO_H
