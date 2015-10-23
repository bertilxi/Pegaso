/**
 * Project Pegaso
 */


#include "Competencia.h"

/**
 * Competencia implementation
 */



Modalidad Competencia::getModalidad() const
{
    return modalidad;
}

void Competencia::setModalidad(const Modalidad &value)
{
    modalidad = value;
}


Deporte Competencia::getDeporte() const
{
    return deporte;
}

void Competencia::setDeporte(const Deporte &value)
{
    deporte = value;
}
int Competencia::getId() const
{
    return id;
}

void Competencia::setId(int value)
{
    id = value;
}
QString Competencia::getEstado() const
{
    return estado;
}

void Competencia::setEstado(const QString &value)
{
    estado = value;
}
QString Competencia::getNombre() const
{
    return nombre;
}

void Competencia::setNombre(const QString &value)
{
    nombre = value;
}
QVector<Disponibilidad> Competencia::getDisponibilidades() const
{
    return disponibilidades;
}

void Competencia::setDisponibilidades(const QVector<Disponibilidad> &value)
{
    disponibilidades = value;
}
QVector<Participante> Competencia::getParticipantes() const
{
    return participantes;
}

void Competencia::setParticipantes(const QVector<Participante> &value)
{
    participantes = value;
}
QVector<Partido> Competencia::getPartidos() const
{
    return partidos;
}

void Competencia::setPartidos(const QVector<Partido> &value)
{
    partidos = value;
}





