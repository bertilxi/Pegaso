/**
 * Project Pegaso
 */


#ifndef _DISPONIBILIDAD_H
#define _DISPONIBILIDAD_H

#include "Lugar.h"


class Disponibilidad {
public: 
    Lugar getLugar() const;
    void setLugar(const Lugar &value);

    int getDisponibilidad() const;
    void setDisponibilidad(int value);

private:
    Lugar lugar;
    int disponibilidad;
};

#endif //_DISPONIBILIDAD_H
