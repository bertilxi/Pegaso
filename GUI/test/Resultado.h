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

    void setResultadoA(Res *value);

    void setResultadoB(Res *value);

    Res *getResultadoA() const;

    Res *getResultadoB() const;

    virtual ~Resultado();

protected:

    int id;

    Res* resultadoA;

    Res* resultadoB;

};

#endif //_RESULTADO_H
