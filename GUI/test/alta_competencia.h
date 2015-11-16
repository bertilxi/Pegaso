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

    explicit alta_competencia(GUI* guiP,QVector<Deporte*> deportesP, QVector<Lugar *> lugaresP,
                              QVector<TipoModalidad*> modalidadesP, QVector<TipoResultado*> resultadosP, QWidget *parent = 0);
    ~alta_competencia();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    GUI* gui;
    int rowCount;
    QVector<Lugar*> lugar;
    QVector<Deporte*> deportes;
    QVector<TipoModalidad*> modalidades;
    int maxSet;
    bool conEmpate;
    QVector<TipoModalidad*> tiposModalidades;
    Ui::alta_competencia *ui;

    int buscarDeporte(QString deporte);
    int buscarTipoMod(QString modalidad);
};

#endif // ALTA_COMPETENCIA_H
