/**
 * Project Pegaso
 */


#include "Localidad.h"

/**
 * Localidad implementation
 */

int Localidad::getId() const
{
    return id;
}

void Localidad::setId(int value)
{
    id = value;
}

QString Localidad::getNombre() const
{
    return nombre;
}

void Localidad::setNombre(const QString &value)
{
    nombre = value;
}

Provincia *Localidad::getProvincia() const
{
    return provincia;
}

void Localidad::setProvincia(Provincia *value)
{
    provincia = value;
}
