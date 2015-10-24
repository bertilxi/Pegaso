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


