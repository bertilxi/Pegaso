#include "tipomodalidad.h"


QString TipoModalidad::getNombre()
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
