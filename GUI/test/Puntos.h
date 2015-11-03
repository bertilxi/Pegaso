/**
 * Project Pegaso
 */


#ifndef _PUNTOS_H
#define _PUNTOS_H

#include <QDebug>
#include "Resultado.h"


class Puntos: public Resultado {
public:


    bool operator==(const Puntos &other)const;

    QString getTable() const;

    QVector<Atributo> getAtributos() const;



    int getPuntosA() const;
    void setPuntosA(int value);

    int getPuntosB() const;
    void setPuntosB(int value);

    int puntosB;
    int puntosA;

private:
};

#endif //_PUNTOS_H
