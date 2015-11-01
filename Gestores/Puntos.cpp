/**
 * Project Pegaso
 */


#include "Puntos.h"

/**
 * Puntos implementation
 */


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
    return 1;
}

QString Puntos::getTable() const{
    return "Puntos";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Puntos con el correspondiente nombre
 * de sus columnas en la tabla Puntos de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Puntos::getAtributos() const{
    QVector<Atributo> result;
    result.push_back(Atributo("puntosA", QString::number(puntosA)));
    result.push_back(Atributo("puntosB", QString::number(puntosB)));

    return result;
}

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


