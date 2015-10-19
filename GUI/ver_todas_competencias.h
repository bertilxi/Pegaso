#ifndef VER_TODAS_COMPETENCIAS_H
#define VER_TODAS_COMPETENCIAS_H

#include <QDialog>

namespace Ui {
class ver_todas_competencias;
}

class ver_todas_competencias : public QDialog
{
    Q_OBJECT

public:
    explicit ver_todas_competencias(QWidget *parent = 0);
    ~ver_todas_competencias();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ver_todas_competencias *ui;
};

#endif // VER_TODAS_COMPETENCIAS_H
