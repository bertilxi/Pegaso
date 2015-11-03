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
#include "res.h"

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

    bool virtual operator==(const Resultado &other) const;

    QString getTable() const;

    QVector<Atributo> getAtributos() const;

    Res *getResultadoA() ;
    void setResultadoA(Res *value);

    Res *getResultadoB() ;
    void setResultadoB(Res *value);

protected:
    int id;
    Res* resultadoA;
    Res* resultadoB;
};

#endif //_RESULTADO_H
