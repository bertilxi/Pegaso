/**
 * Project Pegaso
 */


#include "Provincia.h"

/**
 * Provincia implementation
 */

QVector<Localidad *> Provincia::getLocalidades() const
{
    return localidades;
}

void Provincia::setLocalidades(const QVector<Localidad *> &value)
{
    localidades = value;
}

int Provincia::getId() const
{
    return id;
}

void Provincia::setId(int value)
{
    id = value;
}

QString Provincia::getNombre() const
{
    return nombre;
}

void Provincia::setNombre(const QString &value)
{
    nombre = value;
}
