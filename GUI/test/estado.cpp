#include "estado.h"


QString Estado::getNombre()
{
    return nombre;
}

void Estado::setNombre(const QString &value)
{
    nombre = value;
}

int Estado::getId() const
{
    return id;
}

void Estado::setId(int value)
{
    id = value;
}
