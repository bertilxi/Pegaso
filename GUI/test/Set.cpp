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
    return 1;
}

QString Set::getTable() const{
    return "Sets";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Set con el correspondiente nombre
 * de sus columnas en la tabla Sets de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Set::getAtributos() const{
    QVector<Atributo> result;
    result.push_back(Atributo("nro_set", QString::number(nro_set)));
    result.push_back(Atributo("puntosA", QString::number(puntosA)));
    result.push_back(Atributo("puntosB", QString::number(puntosB)));

    return result;
}

Set::Set()
{
    nro_set =-1;
    puntosA = -1;
    puntosB = -1;
}

