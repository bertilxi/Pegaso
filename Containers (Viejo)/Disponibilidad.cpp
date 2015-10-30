/**
 * Project Pegaso
 */


#include "Disponibilidad.h"

/**
 * Disponibilidad implementation
 */


int Disponibilidad::getDisponibilidad() const
{
    return disponibilidad;
}

void Disponibilidad::setDisponibilidad(int value)
{
    disponibilidad = value;
}
Lugar *Disponibilidad::getLugar() const
{
    return lugar;
}

void Disponibilidad::setLugar(Lugar *value)
{
    lugar = value;
}

bool Disponibilidad::operator==(const Disponibilidad &other) const
{
    if(other.getDisponibilidad()!=disponibilidad){
        qDebug()<<"Disponibilidad: "<<other.getDisponibilidad()<<" "<<disponibilidad;
        return 0;
    }
    if(!(*(other.getLugar()) == *lugar)){
        qDebug()<<" en disponibilidad";
        return 0;
    }
    return 1;
}

QString Disponibilidad::getTable(){
    return "Se_asignan";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Disponibilidad con el correspondiente nombre
 * de sus columnas en la tabla Se_asignan de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Disponibilidad::getAtributos() const{
    QVector<Atributo> result;

    result.push_back(Atributo("id_lugar", QString::number(lugar->getId())));
    result.push_back(Atributo("disponibilidad", QString::number(disponibilidad)));

    return result;
}


