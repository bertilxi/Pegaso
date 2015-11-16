/**
 * Project Pegaso
 */


#ifndef _DISPONIBILIDAD_H
#define _DISPONIBILIDAD_H

#include "Lugar.h"
#include "Atributo.h"
#include <QDebug>

class Disponibilidad {
public: 

    void setId(int value) {/*no hacer nada*/}

    int getDisponibilidad() const;

    void setDisponibilidad(int value);

    Lugar *getLugar() const;

    void setLugar(Lugar *value);

    bool operator==(const Disponibilidad &other)const;

    QString getTable();

    QVector<Atributo> getAtributos() const;

private:

    Lugar *lugar;

    int disponibilidad;
};

#endif //_DISPONIBILIDAD_H
