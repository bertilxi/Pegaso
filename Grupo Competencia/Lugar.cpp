/**
 * Project Pegaso
 */


#include "Lugar.h"

/**
 * Lugar implementation
 */

int Lugar::getId() const
{
    return id;
}

void Lugar::setId(int value)
{
    id = value;
}
QString Lugar::getNombre() const
{
    return nombre;
}

void Lugar::setNombre(const QString &value)
{
    nombre = value;
}
QString Lugar::getDescripcion() const
{
    return descripcion;
}

void Lugar::setDescripcion(const QString &value)
{
    descripcion = value;
}


