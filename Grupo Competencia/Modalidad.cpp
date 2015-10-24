/**
 * Project Pegaso
 */


#include "Modalidad.h"

/**
 * Modalidad implementation
 */

int Modalidad::getId() const
{
    return id;
}

void Modalidad::setId(int value)
{
    id = value;
}
QString Modalidad::getNombre() const
{
    return nombre;
}

void Modalidad::setNombre(const QString &value)
{
    nombre = value;
}
QString Modalidad::getTipo_resultado() const
{
    return tipo_resultado;
}

void Modalidad::setTipo_resultado(const QString &value)
{
    tipo_resultado = value;
}
int Modalidad::getCant_max_sets() const
{
    return cant_max_sets;
}

void Modalidad::setCant_max_sets(int value)
{
    cant_max_sets = value;
}
int Modalidad::getPuntos_presentarse() const
{
    return puntos_presentarse;
}

void Modalidad::setPuntos_presentarse(int value)
{
    puntos_presentarse = value;
}
int Modalidad::getPuntos_ganar() const
{
    return puntos_ganar;
}

void Modalidad::setPuntos_ganar(int value)
{
    puntos_ganar = value;
}
bool Modalidad::getEmpate() const
{
    return empate;
}

void Modalidad::setEmpate(bool value)
{
    empate = value;
}
int Modalidad::getPuntos_empate() const
{
    return puntos_empate;
}

void Modalidad::setPuntos_empate(int value)
{
    puntos_empate = value;
}

bool Modalidad::operator==(const Modalidad &other) const
{
    if(other.getCant_max_sets()!=cant_max_sets){
        qDebug()<<"cant_max_sets: "<<other.getCant_max_sets()<<" "<<cant_max_sets<<" en modalidad "<<id;
        return 0;
    }
    if(other.getEmpate()!=empate){
        qDebug()<<"Empate: "<<other.getEmpate()<<" "<<empate<<" en modalidad "<<id;
        return 0;
    }
    if(other.getNombre()!=nombre){
        qDebug()<<"Nombre: "<<other.getNombre()<<" "<<nombre<<" en modalidad "<<id;
        return 0;
    }
    if(other.getPuntos_empate()!=puntos_empate){
        qDebug()<<"Puntos_empate: "<<other.getPuntos_empate()<<" "<<puntos_empate<<" en modalidad "<<id;
        return 0;
    }
    if(other.puntos_ganar()!=puntos_ganar){
        qDebug()<<"Puntos_ganar: "<<other.puntos_ganar()<<" "<<puntos_ganar<<" en modalidad "<<id;
        return 0;
    }
    if(other.puntos_presentarse()!=puntos_presentarse){
        qDebug()<<"Puntos_presentarse: "<<other.puntos_presentarse()<<" "<<puntos_presentarse<<" en modalidad "<<id;
        return 0;
    }
    if(other.getTipo_resultado()!=tipo_resultado){
        qDebug()<<"Tipo_Resultado: "<<other.getTipo_resultado()<<" "<<tipo_resultado<<" en modalidad "<<id;
        return 0;
    }
    return 1;
}







