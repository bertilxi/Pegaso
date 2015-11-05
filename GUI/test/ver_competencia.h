#ifndef VER_COMPETENCIA_H
#define VER_COMPETENCIA_H

#include <QDialog>
#include "Competencia.h"

namespace Ui {
class ver_competencia;
}

class ver_competencia : public QDialog
{
    Q_OBJECT

public:
    explicit ver_competencia(QWidget *parent = 0);
    explicit ver_competencia(Competencia *comp, QWidget *parent = 0);
    ~ver_competencia();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    //void on_pushButton_3_clicked();

    //void on_pushButton_5_clicked();

//    void on_pushButton_4_clicked();

  //  void on_pushButton_6_clicked();

//    void on_pushButton_clicked();

private:
    Ui::ver_competencia *ui;
};

#endif // VER_COMPETENCIA_H
