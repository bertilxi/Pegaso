/**
 * Project Pegaso
 */


#ifndef _PUNTOS_H
#define _PUNTOS_H

#include <QDebug>
#include "Resultado.h"


class Puntos: public Resultado {
public:
    int getPuntosA() const;
    void setPuntosA(int value);

    int getPuntosB() const;
    void setPuntosB(int value);

    bool operator==(const Puntos &other)const;

    QString getTable() const;

    QVector<Atributo> getAtributos() const;

private:
    int puntosA;
    int puntosB;
};

#endif //_PUNTOS_H
