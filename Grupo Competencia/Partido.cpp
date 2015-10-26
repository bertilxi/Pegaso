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
Participante *Partido::getEquipoA() const
{
    return equipoA;
}

void Partido::setEquipoA(const Participante *value)
{
    equipoA = value;
}
Participante *Partido::getEquipoB() const
{
    return equipoB;
}

void Partido::setEquipoB(const Participante *value)
{
    equipoB = value;
}
Lugar *Partido::getLugar() const
{
    return lugar;
}

void Partido::setLugar(const Lugar *value)
{
    lugar = value;
}
Partido *Partido::getSucesor() const
{
    return sucesor;
}

void Partido::setSucesor(const Partido *value)
{
    sucesor = value;
}
QVector<Resultado *> Partido::getModificado() const
{
    return modificado;
}

void Partido::setModificado(const QVector<Resultado *> &value)
{
    modificado = value;
}
Resultado *Partido::getActual() const
{
    return actual;
}

void Partido::setActual(const Resultado *value)
{
    actual = value;
}

bool Partido::operator==(const Partido &other) const
{
    if(!(*(other.getActual()) == *actual)){
        qDebug()<<" en partido "<<id;
        return 0;
    }
    if(other.getFecha()!=fecha){
        qDebug()<<"Fecha: "<<other.getFecha()<<" "<<fecha<<" en partido "<<id;
        return 0;
    }
    if(other.getRonda()!=ronda){
        qDebug()<<"Ronda: "<<other.getRonda()<<" "<<ronda<<" en partido "<<id;
        return 0;
    }
    if(!(*(other.getEquipoA()) == *equipoA)){
        qDebug()<<" EquipoA en partido "<<id;
        return 0;
    }
    if(!(*(other.getEquipoB()) == *equipoB)){
        qDebug()<<" EquipoB en partido "<<id;
        return 0;
    }
    if(!(*(other.getLugar()) == *lugar)){
        qDebug()<<" en partido "<<id;
        return 0;
    }
    if(!(*(other.getActual()) == *actual)){
        qDebug()<<" en partido "<<id;
        return 0;
    }
    QVector<Resultado *> otherModificado(other.getModificado());
    if(otherModificado.size()!=modificado.size()){
        qDebug()<<"modificados en partido "<<id;
        return 0;
    }
    for(int i=0;i<otherModificado.size();i++){
        if(!(*otherModificado[i] == *modificado[i])){
            qDebug()<<" en partido "<<id;
            return 0;
        }
    }
    QVector<Partido *> otherSucesor(other.getSucesor());
    if(otherSucesor.size()!=sucesor.size()){
        qDebug()<<"Sucesor en partido "<<id;
        return 0;
    }
    for(int i=0;i<otherSucesor.size();i++){
        if(!(*otherSucesor[i] == *sucesor[i])){
            qDebug()<<" en partido "<<id;
            return 0;
        }
    }
    return 1;
}








