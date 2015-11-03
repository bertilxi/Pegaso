#include "estado.h"

int Estado::getId() const
{
    return id;
}

void Estado::setId(int value)
{
    id = value;
}

QString Estado::getNombre()
{
    return nombre;
}

void Estado::setNombre(const QString &value)
{
    nombre = value;
}
