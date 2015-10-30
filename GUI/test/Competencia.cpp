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

bool Competencia::operator==(const Competencia &other) const
{
    QVector<Disponibilidad *> otherDisponibilidades(other.getDisponibilidades());
    if(otherDisponibilidades.size()!=disponibilidades.size()){
        qDebug()<<"Disponibilidades en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherDisponibilidades.size();i++){
        if(!(*otherDisponibilidades[i] == *disponibilidades[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }

    QVector<Participante *> otherParticipantes(other.getParticipantes());
    if(otherParticipantes.size()!=participantes.size()){
        qDebug()<<" Participantes en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherParticipantes.size();i++){
        if(!(*otherParticipantes[i] == *participantes[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }

    QVector<Partido *> otherPartidos(other.getPartidos());
    if(otherPartidos.size()!=partidos.size()){
        qDebug()<<"Partidos en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherPartidos.size();i++){
        if(!(*otherPartidos[i] == *partidos[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }
    if(!(*(other.getDeporte()) == *deporte)){
        qDebug()<<" en competencia"<<id;
        return 0;
    }
    if(!(*(other.getModalidad()) == *modalidad)){
        qDebug()<<" en competencia"<<id;
        return 0;
    }
    if(other.getEstado()!=estado){
        qDebug()<<"Estado: "<<other.getEstado()<<" "<<estado<<" en competencia"<<id;
        return 0;
    }
    return 1;
}
QString Competencia::getFecha_y_horaB() const
{
    return fecha_y_horaB;
}

void Competencia::setFecha_y_horaB(const QString &value)
{
    fecha_y_horaB = value;
}
bool Competencia::getBorrado() const
{
    return borrado;
}

void Competencia::setBorrado(bool value)
{
    borrado = value;
}










QString Competencia::getReglamento() const
{
    return reglamento;
}

void Competencia::setReglamento(const QString &value)
{
    reglamento = value;
}

QString Competencia::getTable(){
    return "Competencia";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Competencia con el correspondiente nombre
 * de sus columnas en la tabla Competencia de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Competencia::getAtributos() const{
    QVector<Atributo> result;
    if(id != -1){
        result.push_back(Atributo("id_competencia",QString::number(id)));
    }
    result.push_back(Atributo("nombre",nombre));
    result.push_back(Atributo("fecha_y_horaB", fecha_y_horaB));
    result.push_back(Atributo("borrado", QString::number((int)borrado)));
    result.push_back(Atributo("estado", estado));
    result.push_back(Atributo("id_modalidad", QString::number(modalidad->getId())));
    result.push_back(Atributo("id_deporte", QString::number(deporte->getId())));

    return result;
}