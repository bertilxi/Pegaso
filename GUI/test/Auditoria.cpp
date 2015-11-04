/**
 * Project Pegaso
 */


#include "Auditoria.h"

/**
 * Auditoria implementation
 */
QString Auditoria::getPc() const
{
    return pc;
}

void Auditoria::setPc(const QString &value)
{
    pc = value;
}
QString Auditoria::getFecha() const
{
    return fecha;
}

void Auditoria::setFecha(const QString &value)
{
    fecha = value;
}

