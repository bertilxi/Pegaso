#ifndef LISTAR_COMPETENCIAS_H
#define LISTAR_COMPETENCIAS_H

#include <QDialog>

namespace Ui {
class listar_competencias;
}

class listar_competencias : public QDialog
{
    Q_OBJECT

public:
    explicit listar_competencias(QWidget *parent = 0);
    ~listar_competencias();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::listar_competencias *ui;
};

#endif // LISTAR_COMPETENCIAS_H
