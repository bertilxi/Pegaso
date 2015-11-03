/**
 * Project Pegaso
 */


#include "Resultado.h"


/**
 * Resultado implementation
 */

int Resultado::getId() const
{
    return id;
}

void Resultado::setId(int value)
{
    id = value;
}

bool Resultado::operator==(const Resultado &other) const
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

QString Resultado::getTable() const{
    return "Resultado";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Resultado con el correspondiente nombre
 * de sus columnas en la tabla Resultado de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Resultado::getAtributos() const{
    QVector<Atributo> result;
    if(id != -1){
        result.push_back(Atributo("id_resultado",QString::number(id)));
    }
    result.push_back(Atributo("resultadoA", resultadoA));
    result.push_back(Atributo("resultadoB", resultadoB));

    return result;
}

Res *Resultado::getResultadoA()
{
    return resultadoA;
}

void Resultado::setResultadoA(Res *value)
{
    resultadoA = value;
}

Res *Resultado::getResultadoB()
{
    return resultadoB;
}

void Resultado::setResultadoB(Res *value)
{
    resultadoB = value;
}

