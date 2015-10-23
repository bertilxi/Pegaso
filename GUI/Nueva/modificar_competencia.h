#ifndef MODIFICAR_COMPETENCIA_H
#define MODIFICAR_COMPETENCIA_H

#include <QDialog>

namespace Ui {
class modificar_competencia;
}

class modificar_competencia : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_competencia(QWidget *parent = 0);
    ~modificar_competencia();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::modificar_competencia *ui;
};

#endif // MODIFICAR_COMPETENCIA_H
