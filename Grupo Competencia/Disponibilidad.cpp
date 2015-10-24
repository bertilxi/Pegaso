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

}


