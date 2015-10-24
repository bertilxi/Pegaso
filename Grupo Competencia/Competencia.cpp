/**
 * Project Pegaso
 */


#include "Competencia.h"

/**
 * Competencia implementation
 */







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
QVector<Disponibilidad *> Competencia::getDisponibilidades() const
{
    return disponibilidades;
}

void Competencia::setDisponibilidades(const QVector<Disponibilidad *> &value)
{
    disponibilidades = value;
}
QVector<Participante *> Competencia::getParticipantes() const
{
    return participantes;
}

void Competencia::setParticipantes(const QVector<Participante *> &value)
{
    participantes = value;
}
Modalidad *Competencia::getModalidad() const
{
    return modalidad;
}

void Competencia::setModalidad(Modalidad *value)
{
    modalidad = value;
}
QVector<Partido *> Competencia::getPartidos() const
{
    return partidos;
}

void Competencia::setPartidos(const QVector<Partido *> &value)
{
    partidos = value;
}
Deporte *Competencia::getDeporte() const
{
    return deporte;
}

void Competencia::setDeporte(Deporte *value)
{
    deporte = value;
}







