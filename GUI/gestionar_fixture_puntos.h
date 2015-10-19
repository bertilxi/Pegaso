#ifndef GESTIONAR_FIXTURE_PUNTOS_H
#define GESTIONAR_FIXTURE_PUNTOS_H

#include <QDialog>

namespace Ui {
class gestionar_fixture_puntos;
}

class gestionar_fixture_puntos : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture_puntos(QWidget *parent = 0);
    ~gestionar_fixture_puntos();

private:
    Ui::gestionar_fixture_puntos *ui;
};

#endif // GESTIONAR_FIXTURE_PUNTOS_H
