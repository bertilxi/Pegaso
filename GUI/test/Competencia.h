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
#include "estado.h"


class Competencia {
public: 

    int getId() const;

    void setId(int value);

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

    bool operator==(Competencia &other);

    QString getFecha_y_horaB() const;

    void setFecha_y_horaB(const QString &value);

    bool getBorrado() const;

    void setBorrado(bool value);

    QString getReglamento() const;

    void setReglamento(const QString &value);

    QString getTable();

    QVector<Atributo> getAtributos() const;

    Estado *getEstado() ;

    void setEstado(Estado *value);

    QVector<Partido*> getProximosEncuentros();

    int getFechaActual();

    Competencia(): fechaActual(-1) {}


private:

    int id;

    Estado* estado;

    QString nombre;

    QString fecha_y_horaB;

    bool borrado;

    int fechaActual;

    QString reglamento;

    QVector<Disponibilidad *> disponibilidades;

    QVector<Participante *> participantes;

    Modalidad *modalidad;

    QVector<Partido *> partidos;

    Deporte *deporte;
};

#endif //_COMPETENCIA_H
