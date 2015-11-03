#include "estado.h"

Estado::Estado()
{

}


int Estado::getId() const
{
    return id;
}

void Estado::setId(int value)
{
    id = value;
}

QString Estado::getNombre() const
{
    return nombre;
}

void Estado::setNombre(const QString &value)
{
    nombre = value;
}
