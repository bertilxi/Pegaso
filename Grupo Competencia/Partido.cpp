/**
 * Project Pegaso
 */


#include "Partido.h"

/**
 * Partido implementation
 */

int Partido::getId() const
{
    return id;
}

void Partido::setId(int value)
{
    id = value;
}
QString Partido::getRonda() const
{
    return ronda;
}

void Partido::setRonda(const QString &value)
{
    ronda = value;
}
int Partido::getFecha() const
{
    return fecha;
}

void Partido::setFecha(int value)
{
    fecha = value;
}
Participante Partido::getEquipoA() const
{
    return equipoA;
}

void Partido::setEquipoA(const Participante &value)
{
    equipoA = value;
}
Participante Partido::getEquipoB() const
{
    return equipoB;
}

void Partido::setEquipoB(const Participante &value)
{
    equipoB = value;
}
Lugar Partido::getLugar() const
{
    return lugar;
}

void Partido::setLugar(const Lugar &value)
{
    lugar = value;
}
Partido Partido::getSucesor() const
{
    return sucesor;
}

void Partido::setSucesor(const Partido &value)
{
    sucesor = value;
}
QVector<Resultado> Partido::getModificado() const
{
    return modificado;
}

void Partido::setModificado(const QVector<Resultado> &value)
{
    modificado = value;
}
Resultado Partido::getActual() const
{
    return actual;
}

void Partido::setActual(const Resultado &value)
{
    actual = value;
}








