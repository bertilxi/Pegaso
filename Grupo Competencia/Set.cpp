/**
 * Project Pegaso
 */


#include "Set.h"

/**
 * Set implementation
 */

int Set::getNro_set() const
{
    return nro_set;
}

void Set::setNro_set(int value)
{
    nro_set = value;
}
int Set::getPuntosA() const
{
    return puntosA;
}

void Set::setPuntosA(int value)
{
    puntosA = value;
}
int Set::getPuntosB() const
{
    return puntosB;
}

void Set::setPuntosB(int value)
{
    puntosB = value;
}

bool Set::operator==(const Set &other) const
{
    if(other.getNro_set()!=nro_set){
        qDebug()<<"Nro_set: "<<other.getNro_set()<<" "<<nro_set;
        return 0;
    }
    if(other.getPuntosA()!=puntosA){
        qDebug()<<"PuntosA: "<<other.getPuntosA()<<" "<<puntosA;
        return 0;
    }
    if(other.getPuntosB()!=puntosB){
        qDebug()<<"PuntosB: "<<other.getPuntosB()<<" "<<puntosB;
        return 0;
    }
}


