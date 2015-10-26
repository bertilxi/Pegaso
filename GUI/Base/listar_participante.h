#ifndef LISTAR_PARTICIPANTE_H
#define LISTAR_PARTICIPANTE_H

#include <QDialog>

namespace Ui {
class listar_participante;
}

class listar_participante : public QDialog
{
    Q_OBJECT

public:
    explicit listar_participante(QWidget *parent = 0);
    ~listar_participante();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::listar_participante *ui;
};

#endif // LISTAR_PARTICIPANTE_H
