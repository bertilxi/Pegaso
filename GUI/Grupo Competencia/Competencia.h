/**
 * Project Pegaso
 */


#ifndef _COMPETENCIA_H
#define _COMPETENCIA_H

#include <QString>
#include <QVector>
#include <QDebug>
#include "Disponibilidad.h"
#include "Participante.h"
#include "Modalidad.h"
#include "Partido.h"
#include "Deporte.h"


class Competencia {
public: 

    int getId() const;
    void setId(int value);

    QString getEstado() const;
    void setEstado(const QString value);

    QString getNombre() const;
    void setNombre(const QString value);

    QVector<Disponibilidad *> getDisponibilidades() const;
    void setDisponibilidades(const QVector<Disponibilidad *> value);

    QVector<Participante *> getParticipantes() const;
    void setParticipantes(const QVector<Participante *> value);

    Modalidad *getModalidad() const;
    void setModalidad(Modalidad *value);

    QVector<Partido *> getPartidos() const;
    void setPartidos(const QVector<Partido *> value);

    Deporte *getDeporte() const;
    void setDeporte(Deporte *value);

    bool operator==(const Competencia other)const;

    QString getFecha_y_horaB() const;
    void setFecha_y_horaB(const QString value);

    bool getBorrado() const;
    void setBorrado(bool value);

    QString getReglamento() const;
    void setReglamento(const QString value);

    QString getTable();

    /**
     * @brief getAtributos
     * @return una lista de los atributos de Competencia con el correspondiente nombre
     * de sus columnas en la tabla Competencia de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

private:
    int id;
    QString estado;
    QString nombre;
    QString fecha_y_horaB;
    bool borrado;
    QString reglamento;
    QVector<Disponibilidad *> disponibilidades;
    QVector<Participante *> participantes;
    Modalidad *modalidad;
    QVector<Partido *> partidos;
    Deporte *deporte;
};

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

void Competencia::setEstado(const QString value)
{
    estado = value;
}
QString Competencia::getNombre() const
{
    return nombre;
}

void Competencia::setNombre(const QString value)
{
    nombre = value;
}
QVector<Disponibilidad *> Competencia::getDisponibilidades() const
{
    return disponibilidades;
}

void Competencia::setDisponibilidades(const QVector<Disponibilidad *> value)
{
    disponibilidades = value;
}
QVector<Participante *> Competencia::getParticipantes() const
{
    return participantes;
}

void Competencia::setParticipantes(const QVector<Participante *> value)
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

void Competencia::setPartidos(const QVector<Partido *> value)
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

bool Competencia::operator==(const Competencia other) const
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

void Competencia::setFecha_y_horaB(const QString value)
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

void Competencia::setReglamento(const QString value)
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


#endif //_COMPETENCIA_H
