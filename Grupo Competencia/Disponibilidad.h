/**
 * Project Pegaso
 */


#ifndef _DISPONIBILIDAD_H
#define _DISPONIBILIDAD_H

#include "Lugar.h"


class Disponibilidad {
public: 

    int getDisponibilidad() const;
    void setDisponibilidad(int value);

    Lugar *getLugar() const;
    void setLugar(Lugar *value);

private:
    Lugar *lugar;
    int disponibilidad;
};

#endif //_DISPONIBILIDAD_H
