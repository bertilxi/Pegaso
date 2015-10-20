#ifndef MODIFICAR_PARTICIPANTE_H
#define MODIFICAR_PARTICIPANTE_H

#include <QDialog>

namespace Ui {
class modificar_participante;
}

class modificar_participante : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_participante(QWidget *parent = 0);
    ~modificar_participante();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::modificar_participante *ui;
};

#endif // MODIFICAR_PARTICIPANTE_H
