#ifndef GESTIONAR_FIXTURE_SETS_H
#define GESTIONAR_FIXTURE_SETS_H

#include <QDialog>

namespace Ui {
class gestionar_fixture_sets;
}

class gestionar_fixture_sets : public QDialog
{
    Q_OBJECT

public:
    explicit gestionar_fixture_sets(QWidget *parent = 0);
    ~gestionar_fixture_sets();

private:
    Ui::gestionar_fixture_sets *ui;
};

#endif // GESTIONAR_FIXTURE_SETS_H
