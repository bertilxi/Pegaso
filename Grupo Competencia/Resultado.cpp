/**
 * Project Pegaso
 */


#include "Resultado.h"

/**
 * Resultado implementation
 */

QString Resultado::getResultadoA() const
{
    return resultadoA;
}

void Resultado::setResultadoA(const QString &value)
{
    resultadoA = value;
}
QString Resultado::getResultadoB() const
{
    return resultadoB;
}

void Resultado::setResultadoB(const QString &value)
{
    resultadoB = value;
}

bool virtual Resultado::operator==(const Resultado &other) const
{
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

