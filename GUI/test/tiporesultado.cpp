#include "Tiporesultado.h"

TipoResultado::TipoResultado()
{

}


int TipoResultado::getId() const
{
    return id;
}

void TipoResultado::setId(int value)
{
    id = value;
}

QString TipoResultado::getNombre() const
{
    return nombre;
}

void TipoResultado::setNombre(const QString &value)
{
    nombre = value;
}
