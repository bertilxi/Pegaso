/**
 * Project Pegaso
 */


#include "Puntos.h"

/**
 * Puntos implementation
 */

int Puntos::getPuntosA() const
{
    return puntosA;
}

void Puntos::setPuntosA(int value)
{
    puntosA = value;
}
int Puntos::getPuntosB() const
{
    return puntosB;
}

void Puntos::setPuntosB(int value)
{
    puntosB = value;
}

bool Puntos::operator==(const Puntos &other) const
{
    if(other.getPuntosA()!=puntosA){
        qDebug()<<"PuntosA: "<<other.getPuntosA()<<" "<<puntosA<<" en resultado";
        return 0;
    }
    if(other.getPuntosB()!=puntosB){
        qDebug()<<"PuntosB: "<<other.getPuntosB()<<" "<<puntosB<<" en resultado";
        return 0;
    }
    if(other.getResultadoA()!=resultadoA){
        qDebug()<<"ResultadoA: "<<other.getResultadoA()<<" "<<resultadoA<<" en resultado";
        return 0;
    }
    if(other.getResultadoB()!=resultadoB){
        qDebug()<<"ResultadoB: "<<other.getResultadoB()<<" "<<resultadoB<<" en resultado";
        return 0;
    }
    return1;
}

