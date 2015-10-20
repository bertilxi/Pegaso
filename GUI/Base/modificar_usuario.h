#ifndef MODIFICAR_USUARIO_H
#define MODIFICAR_USUARIO_H

#include <QDialog>

namespace Ui {
class modificar_usuario;
}

class modificar_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_usuario(QWidget *parent = 0);
    ~modificar_usuario();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::modificar_usuario *ui;
};

#endif // MODIFICAR_USUARIO_H
