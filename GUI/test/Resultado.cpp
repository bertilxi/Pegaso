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
    if(other.getResultadoA()->getNombre()!=resultadoA->getNombre()){
        qDebug()<<"ResultadoA: "<<other.getResultadoA()->getNombre()<<" "<<resultadoA->getNombre()<<" en resultado";
        return 0;
    }
    if(other.getResultadoB()->getNombre()!=resultadoB->getNombre()){
        qDebug()<<"ResultadoB: "<<other.getResultadoB()->getNombre()<<" "<<resultadoB->getNombre()<<" en resultado";
        return 0;
    }
    return 1;
}

QString Resultado::getTable() const{
    return "Resultado Final";
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
    result.push_back(Atributo("resultadoA", resultadoA->getNombre()));
    result.push_back(Atributo("resultadoB", resultadoB->getNombre()));

    return result;
}


void Resultado::setResultadoA(Res *value)
{
    resultadoA = value;
}



void Resultado::setResultadoB(Res *value)
{
    resultadoB = value;
}

Res *Resultado::getResultadoA() const
{
    return resultadoA;
}

Res *Resultado::getResultadoB() const
{
    return resultadoB;
}

