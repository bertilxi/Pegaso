#ifndef ALTA_COMPETENCIA_H
#define ALTA_COMPETENCIA_H

#include <QDialog>

namespace Ui {
class alta_competencia;
}

class alta_competencia : public QDialog
{
    Q_OBJECT

public:
    explicit alta_competencia(QWidget *parent = 0);
    ~alta_competencia();

private:
    Ui::alta_competencia *ui;
};

#endif // ALTA_COMPETENCIA_H
