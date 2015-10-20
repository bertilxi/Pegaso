#ifndef LISTAR_LUGARES_H
#define LISTAR_LUGARES_H

#include <QDialog>

namespace Ui {
class listar_lugares;
}

class listar_lugares : public QDialog
{
    Q_OBJECT

public:
    explicit listar_lugares(QWidget *parent = 0);
    ~listar_lugares();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::listar_lugares *ui;
};

#endif // LISTAR_LUGARES_H
