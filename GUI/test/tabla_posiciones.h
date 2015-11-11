#ifndef TABLA_POSICIONES_H
#define TABLA_POSICIONES_H

#include <QDialog>

namespace Ui {
class tabla_posiciones;
}

class tabla_posiciones : public QDialog
{
    Q_OBJECT

public:
    explicit tabla_posiciones(QWidget *parent = 0);
    ~tabla_posiciones();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::tabla_posiciones *ui;
};

#endif // TABLA_POSICIONES_H
