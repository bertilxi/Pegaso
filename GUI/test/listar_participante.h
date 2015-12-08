#ifndef LISTAR_PARTICIPANTE_H
#define LISTAR_PARTICIPANTE_H

#include <QDialog>
#include "Participante.h"
#include "gui.h"
#include <QValidator>
#include <QFileDialog>
#include "ver_competencia.h"

class ver_competencia;

namespace Ui {
class listar_participante;
}

class listar_participante : public QDialog
{
    Q_OBJECT

public:
    listar_participante(GUI* guiP,Competencia* compP,ver_competencia* vc, QWidget *parent = 0);
    ~listar_participante();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_7_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::listar_participante *ui;
    QVector<Participante*> participantes;
    Competencia* competencia;
    GUI* gui;
    QString imgUrl;
    ver_competencia* verCompetencia;
};

QT_BEGIN_NAMESPACE

class QRegExp;

QT_END_NAMESPACE



class EmailValidator : public QValidator
{
    Q_OBJECT

public:

    explicit EmailValidator(QObject *parent = 0);

    State validate(QString &text, int &pos) const;

    void fixup(QString &text) const;


private:

    const QRegExp m_validMailRegExp;

    const QRegExp m_intermediateMailRegExp;

};
#endif // LISTAR_PARTICIPANTE_H
