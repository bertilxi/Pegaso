#ifndef GESTIONAR_FIXTURE_H
#define GESTIONAR_FIXTURE_H

#include <QDialog>

namespace Ui {
class gestionar_fixture;
}

class gestionar_fixture : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture(QWidget *parent = 0);
    ~gestionar_fixture();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::gestionar_fixture *ui;
};

#endif // GESTIONAR_FIXTURE_H
