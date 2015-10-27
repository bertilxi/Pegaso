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
    void setEstado(const QString &value);

    QString getNombre() const;
    void setNombre(const QString &value);

    QVector<Disponibilidad *> getDisponibilidades() const;
    void setDisponibilidades(const QVector<Disponibilidad *> &value);

    QVector<Participante *> getParticipantes() const;
    void setParticipantes(const QVector<Participante *> &value);

    Modalidad *getModalidad() const;
    void setModalidad(Modalidad *value);

    QVector<Partido *> getPartidos() const;
    void setPartidos(const QVector<Partido *> &value);

    Deporte *getDeporte() const;
    void setDeporte(Deporte *value);

    bool operator==(const Competencia &other)const;

    QString getFecha_y_horaB() const;
    void setFecha_y_horaB(const QString &value);

    bool getBorrado() const;
    void setBorrado(bool value);

private:
    int id;
    QString estado;
    QString nombre;
    QString fecha_y_horaB;
    bool borrado;
    QVector<Disponibilidad *> disponibilidades;
    QVector<Participante *> participantes;
    Modalidad *modalidad;
    QVector<Partido *> partidos;
    Deporte *deporte;
};

#endif //_COMPETENCIA_H
