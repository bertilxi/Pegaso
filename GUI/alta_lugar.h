#ifndef ALTA_LUGAR_H
#define ALTA_LUGAR_H

#include <QDialog>

namespace Ui {
class alta_lugar;
}

class alta_lugar : public QDialog
{
    Q_OBJECT

public:
    explicit alta_lugar(QWidget *parent = 0);
    ~alta_lugar();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::alta_lugar *ui;
};

#endif // ALTA_LUGAR_H
