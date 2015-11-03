#include "tipomodalidad.h"

TipoModalidad::TipoModalidad()
{

}


QString TipoModalidad::getNombre() const
{
    return nombre;
}

void TipoModalidad::setNombre(const QString &value)
{
    nombre = value;
}

int TipoModalidad::getId() const
{
    return id;
}

void TipoModalidad::setId(int value)
{
    id = value;
}
