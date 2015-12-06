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

QString HistorialParticipante::getTable(){
    return "Historial_participante";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de HistorialParticipante con el correspondiente nombre
 * de sus columnas en la tabla Historial_participante de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> HistorialParticipante::getAtributos() const{
    QVector<Atributo> result;
    if(id != -1){
        result.push_back(Atributo("id_modificacion",QString::number(id)));
    }
    result.push_back(Atributo("imagen", imagen));
    result.push_back(Atributo("nombre", nombre));
    result.push_back(Atributo("correo", correo));

    return result;
}

HistorialParticipante::HistorialParticipante()
{
    id = -1;
}

