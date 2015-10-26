#ifndef ALTA_COMPETENCIA_LIGA_H
#define ALTA_COMPETENCIA_LIGA_H

#include <QDialog>

namespace Ui {
class alta_competencia_liga;
}

class alta_competencia_liga : public QDialog
{
    Q_OBJECT

public:
    explicit alta_competencia_liga(QWidget *parent = 0);
    ~alta_competencia_liga();

private:
    Ui::alta_competencia_liga *ui;
};

#endif // ALTA_COMPETENCIA_LIGA_H
