/**
 * Project Pegaso
 */


#include "Disponibilidad.h"

/**
 * Disponibilidad implementation
 */

Lugar Disponibilidad::getLugar() const
{
    return lugar;
}

void Disponibilidad::setLugar(const Lugar &value)
{
    lugar = value;
}
int Disponibilidad::getDisponibilidad() const
{
    return disponibilidad;
}

void Disponibilidad::setDisponibilidad(int value)
{
    disponibilidad = value;
}

