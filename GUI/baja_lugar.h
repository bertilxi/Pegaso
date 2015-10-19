#ifndef BAJA_LUGAR_H
#define BAJA_LUGAR_H

#include <QDialog>

namespace Ui {
class baja_lugar;
}

class baja_lugar : public QDialog
{
    Q_OBJECT

public:
    explicit baja_lugar(QWidget *parent = 0);
    ~baja_lugar();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::baja_lugar *ui;
};

#endif // BAJA_LUGAR_H
