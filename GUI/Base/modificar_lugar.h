#ifndef MODIFICAR_LUGAR_H
#define MODIFICAR_LUGAR_H

#include <QDialog>

namespace Ui {
class modificar_lugar;
}

class modificar_lugar : public QDialog
{
    Q_OBJECT

public:
    explicit modificar_lugar(QWidget *parent = 0);
    ~modificar_lugar();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::modificar_lugar *ui;
};

#endif // MODIFICAR_LUGAR_H
