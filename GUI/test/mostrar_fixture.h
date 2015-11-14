#ifndef MOSTRAR_FIXTURE_H
#define MOSTRAR_FIXTURE_H

#include <QDialog>
#include "Partido.h"

namespace Ui {
class mostrar_fixture;
}

class mostrar_fixture : public QDialog
{
    Q_OBJECT

public:
    explicit mostrar_fixture(QWidget *parent = 0);
    explicit mostrar_fixture(QVector<Partido*> partidosP,QWidget *parent = 0);

    ~mostrar_fixture();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mostrar_fixture *ui;
};

#endif // MOSTRAR_FIXTURE_H
