#ifndef ALTA_COMPETENCIA_H
#define ALTA_COMPETENCIA_H

#include <QDialog>
#include <QVector>
#include <QMessageBox>
#include "tipomodalidad.h"
#include "Deporte.h"
#include "Disponibilidad.h"
#include "gui.h"


class GUI;
namespace Ui {
class alta_competencia;
}

class alta_competencia : public QDialog
{
    Q_OBJECT

public:
    explicit alta_competencia(QWidget *parent = 0);
    explicit alta_competencia(QVector<Deporte*> deportes, QVector<Lugar *> lugares, QVector<TipoModalidad*> modalidades, QWidget *parent = 0);
    ~alta_competencia();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    GUI* gui;
    QVector<Lugar*> lugar;
    Ui::alta_competencia *ui;
};

#endif // ALTA_COMPETENCIA_H
