#include "res.h"

int Res::getId() const
{
    return id;
}

void Res::setId(int value)
{
    id = value;
}

QString Res::getNombre() const
{
    return nombre;
}

void Res::setNombre(const QString &value)
{
    nombre = value;
}

Res::Res()
{
    id = -1;
}
