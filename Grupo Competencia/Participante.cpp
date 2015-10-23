/**
 * Project Pegaso
 */


#include "Participante.h"

/**
 * Participante implementation
 */

int Participante::getId() const
{
    return id;
}

void Participante::setId(int value)
{
    id = value;
}
QString Participante::getNombre() const
{
    return nombre;
}

void Participante::setNombre(const QString &value)
{
    nombre = value;
}
QString Participante::getCorreo() const
{
    return correo;
}

void Participante::setCorreo(const QString &value)
{
    correo = value;
}
QString Participante::getImg() const
{
    return img;
}

void Participante::setImg(const QString &value)
{
    img = value;
}
QVector<HistorialParticipante> Participante::getHistorial() const
{
    return historial;
}

void Participante::setHistorial(const QVector<HistorialParticipante> &value)
{
    historial = value;
}
Puntaje Participante::getPuntaje() const
{
    return puntaje;
}

void Participante::setPuntaje(const Puntaje &value)
{
    puntaje = value;
}





