/**
 * Project Pegaso
 */

#ifndef _RESULTADO_H
#define _RESULTADO_H

#include <QVector>
#include <QString>
#include <QDebug>
#include "Atributo.h"
#include "Set.h"

class Resultado {
public:
    virtual int getPuntosA() const{}
    virtual int getPuntosB() const{}
    virtual QVector<Set*> getSets(){
        QVector<Set*> a;
        return a;
    }
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
