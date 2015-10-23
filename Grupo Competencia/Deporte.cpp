/**
 * Project Pegaso
 */


#include "Deporte.h"

/**
 * Deporte implementation
 */

int Deporte::getId() const
{
    return id;
}

void Deporte::setId(int value)
{
    id = value;
}
QString Deporte::getNombre() const
{
    return nombre;
}

void Deporte::setNombre(const QString &value)
{
    nombre = value;
}

