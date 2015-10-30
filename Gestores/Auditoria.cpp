/**
 * Project Pegaso
 */


#include "Auditoria.h"

/**
 * Auditoria implementation
 */
QTime Auditoria::getFecha() const
{
    return fecha;
}

void Auditoria::setFecha(const QTime &value)
{
    fecha = value;
}

QString Auditoria::getPc() const
{
    return pc;
}

void Auditoria::setPc(const QString &value)
{
    pc = value;
}
