#ifndef REGISTRAR_USUARIO_H
#define REGISTRAR_USUARIO_H

#include <QDialog>

namespace Ui {
class registrar_usuario;
}

class registrar_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit registrar_usuario(QWidget *parent = 0);
    ~registrar_usuario();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::registrar_usuario *ui;
};

#endif // REGISTRAR_USUARIO_H
