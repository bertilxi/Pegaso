#ifndef GESTIONAR_FIXTURE_RESULTADO_H
#define GESTIONAR_FIXTURE_RESULTADO_H

#include <QDialog>

namespace Ui {
class gestionar_fixture_resultado;
}

class gestionar_fixture_resultado : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture_resultado(QWidget *parent = 0);
    ~gestionar_fixture_resultado();

private:
    Ui::gestionar_fixture_resultado *ui;
};

#endif // GESTIONAR_FIXTURE_RESULTADO_H
