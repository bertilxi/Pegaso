/**
 * Project Pegaso
 */


#include "Doc.h"

/**
 * Doc implementation
 */
QString Doc::getTipo() const
{
    return tipo;
}

void Doc::setTipo(const QString &value)
{
    tipo = value;
}
int Doc::getId() const
{
    return id;
}

void Doc::setId(int value)
{
    id = value;
}

Doc::Doc()
{
    id = -1;
}

