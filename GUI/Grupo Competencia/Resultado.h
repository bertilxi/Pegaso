/**
 * Project Pegaso
 */

#ifndef _RESULTADO_H
#define _RESULTADO_H

#include <QVector>
#include <QString>
#include <QDebug>
#include "../Gestores/Atributo.h"

class Resultado {
public:

    int getId() const;
    void setId(int value);

    QString getResultadoA() const;
    void setResultadoA(const QString &value);

    QString getResultadoB() const;
    void setResultadoB(const QString &value);

    bool virtual operator==(const Resultado &other) const;

    QString getTable() const;

    QVector<Atributo> getAtributos() const;

protected:
    int id;
    QString resultadoA;
    QString resultadoB;
};

#endif //_RESULTADO_H
