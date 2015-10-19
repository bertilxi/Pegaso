#ifndef BAJA_PARTICIPANTE_H
#define BAJA_PARTICIPANTE_H

#include <QDialog>

namespace Ui {
class baja_participante;
}

class baja_participante : public QDialog
{
    Q_OBJECT

public:
    explicit baja_participante(QWidget *parent = 0);
    ~baja_participante();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::baja_participante *ui;
};

#endif // BAJA_PARTICIPANTE_H
