#include "res.h"

Res::Res()
{

}


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
