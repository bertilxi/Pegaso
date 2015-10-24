/**
 * Project Pegaso
 */


#include "HistorialParticipante.h"

/**
 * HistorialParticipante implementation
 */

int HistorialParticipante::getId() const
{
    return id;
}

void HistorialParticipante::setId(int value)
{
    id = value;
}
QString HistorialParticipante::getNombre() const
{
    return nombre;
}

void HistorialParticipante::setNombre(const QString &value)
{
    nombre = value;
}
QString HistorialParticipante::getCorreo() const
{
    return correo;
}

void HistorialParticipante::setCorreo(const QString &value)
{
    correo = value;
}
QString HistorialParticipante::getImagen() const
{
    return imagen;
}

void HistorialParticipante::setImagen(const QString &value)
{
    imagen = value;
}

bool HistorialParticipante::operator==(const HistorialParticipante &other) const
{
    if(other.getNombre()!=nombre){
        qDebug()<<"Nombre: "<<other.getNombre()<<" "<<nombre<<" en historial "<<id;
        return 0;
    }
    if(other.getCorreo()!=correo){
        qDebug()<<"Correo: "<<other.getCorreo()<<" "<<correo<<" en historial "<<id;
        return 0;
    }
    if(other.getImagen()!=imagen){
        qDebug()<<"Imagen: "<<other.getImagen()<<" "<<imagen<<" en historial "<<id;
        return 0;
    }
    return 1;
}



