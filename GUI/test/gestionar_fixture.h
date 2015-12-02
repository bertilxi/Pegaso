#ifndef GESTIONAR_FIXTURE_H
#define GESTIONAR_FIXTURE_H

#include <QDialog>
#include "gui.h"

namespace Ui {
class gestionar_fixture;
}

class gestionar_fixture : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture(GUI* guiP,QWidget *parent = 0);
    ~gestionar_fixture();

private slots:


private:
    Ui::gestionar_fixture *ui;
    GUI* gui;
};

#endif // GESTIONAR_FIXTURE_H
