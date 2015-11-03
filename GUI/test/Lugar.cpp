/**
 * Project Pegaso
 */


#include "Lugar.h"

/**
 * Lugar implementation
 */

int Lugar::getId() const
{
    return id;
}

void Lugar::setId(int value)
{
    id = value;
}
QString Lugar::getNombre() const
{
    return nombre;
}

void Lugar::setNombre(const QString &value)
{
    nombre = value;
}
QString Lugar::getDescripcion() const
{
    return descripcion;
}

void Lugar::setDescripcion(const QString &value)
{
    descripcion = value;
}

bool Lugar::operator==(const Lugar &other) const
{
    if (other.getDescripcion()!=descripcion){
        qDebug()<<"Descripcion: "<<other.getDescripcion()<<" "<<descripcion<<" en lugar "<<id;
        return 0;
    }
    if(other.getId()!=id){
        qDebug()<<"Id: "<<other.getId()<<" "<<id<<" en lugar";
        return 0;
    }
    if(other.getNombre()!=nombre){
        qDebug()<<"Nombre: "<<other.getNombre()<<" "<<nombre<<" en lugar"<<id;
        return 0;
    }
    return 1;
}


