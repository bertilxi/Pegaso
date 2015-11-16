/**
 * Project Pegaso
 */


#ifndef _SET_H
#define _SET_H

#include <QDebug>
#include "Atributo.h"

class Set {
public:

    void setId(int value) {}

    int getNro_set() const;

    void setNro_set(int value);

    int getPuntosA() const;

    void setPuntosA(int value);

    int getPuntosB() const;

    void setPuntosB(int value);

    bool operator==(const Set &other)const;

    QString getTable() const;

    QVector<Atributo> getAtributos() const;


private:

    int nro_set;

    int puntosA;

    int puntosB;

};

#endif //_SET_H
