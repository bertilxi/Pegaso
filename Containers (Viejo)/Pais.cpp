/**
 * Project Pegaso
 */


#include "Pais.h"

/**
 * Pais implementation
 */

Vector<Provincia> Pais::getProvincias() const
{
    return provincias;
}

void Pais::setProvincias(const Vector<Provincia> &value)
{
    provincias = value;
}

int Pais::getId() const
{
    return id;
}

void Pais::setId(int value)
{
    id = value;
}

QString Pais::getNombre() const
{
    return nombre;
}

void Pais::setNombre(const QString &value)
{
    nombre = value;
}
