#ifndef LISTAR_COMPETENCIAS_H
#define LISTAR_COMPETENCIAS_H

#include <QDialog>
#include "ui_listar_competencias.h"
#include "qpixmap.h"
#include <QDebug>
#include "gui.h"

namespace Ui {
class listar_competencias;
}

class GUI;
class listar_competencias : public QDialog
{
    Q_OBJECT

public:
    explicit listar_competencias(QVector<Deporte*> deportes, QVector<Estado*> estados, QVector<TipoModalidad *> modalidades, QWidget *parent = 0);
    listar_competencias(QWidget *parent = 0);
    ~listar_competencias();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    GUI* gui;
    QVector<Competencia*> comps;
    Ui::listar_competencias *ui;

    void mostrarCompetencias();
};

#endif // LISTAR_COMPETENCIAS_H
