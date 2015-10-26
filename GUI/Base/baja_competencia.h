#ifndef BAJA_COMPETENCIA_H
#define BAJA_COMPETENCIA_H

#include <QDialog>

namespace Ui {
class baja_competencia;
}

class baja_competencia : public QDialog
{
    Q_OBJECT

public:
    explicit baja_competencia(QWidget *parent = 0);
    ~baja_competencia();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::baja_competencia *ui;
};

#endif // BAJA_COMPETENCIA_H
