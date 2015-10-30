#ifndef PANTALLA_USUARIO_H
#define PANTALLA_USUARIO_H

#include <QDialog>

namespace Ui {
class pantalla_usuario;
}

class pantalla_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit pantalla_usuario(QWidget *parent = 0);
    ~pantalla_usuario();

private slots:
//    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

private:
    Ui::pantalla_usuario *ui;
};

#endif // PANTALLA_USUARIO_H
