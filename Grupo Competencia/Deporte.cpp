/**
 * Project Pegaso
 */


#include "Deporte.h"

/**
 * Deporte implementation
 */

int Deporte::getId() const
{
    return id;
}

void Deporte::setId(int value)
{
    id = value;
}
QString Deporte::getNombre() const
{
    return nombre;
}

void Deporte::setNombre(const QString &value)
{
    nombre = value;
}

bool Deporte::operator==(const Deporte &other) const
{
    if(other.getNombre()!=nombre){
        qDebug()<<"Nombre: "<<other.getNombre()<<" "<<nombre<<" en deporte "<<id;
        return 0;
    }
    if(other.getId()!=id){
        qDebug()<<"Id: "<<other.getId()<<" "<<id<<" en deporte";
        return 0;
    }
}

