#ifndef ALTA_COMPETENCIA_ELIMINACION_H
#define ALTA_COMPETENCIA_ELIMINACION_H

#include <QDialog>

namespace Ui {
class alta_competencia_eliminacion;
}

class alta_competencia_eliminacion : public QDialog
{
    Q_OBJECT

public:
    explicit alta_competencia_eliminacion(QWidget *parent = 0);
    ~alta_competencia_eliminacion();

private:
    Ui::alta_competencia_eliminacion *ui;
};

#endif // ALTA_COMPETENCIA_ELIMINACION_H
