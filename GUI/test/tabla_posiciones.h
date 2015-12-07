#ifndef TABLA_POSICIONES_H
#define TABLA_POSICIONES_H

#include <QDialog>
#include "Participante.h"
#include "gui.h"
#include "../../Modules/Excel/generadorexcel.h"

namespace Ui {
class tabla_posiciones;
}

class tabla_posiciones : public QDialog
{
    Q_OBJECT

public:

    explicit tabla_posiciones(GUI* guiP, Competencia *compP, QWidget *parent = 0, GeneradorExcel* genExcelP = NULL);

    ~tabla_posiciones();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::tabla_posiciones *ui;
    GUI* gui;
    GeneradorExcel* genExcel;
    Competencia* comp;
};

#endif // TABLA_POSICIONES_H
