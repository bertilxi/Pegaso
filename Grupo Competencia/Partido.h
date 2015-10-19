/**
 * Project Pegaso
 */


#ifndef _PARTIDO_H
#define _PARTIDO_H

#include "Participante.h"
#include "Participante.h"
#include "Lugar.h"
#include "Resultado.h"
#include "Resultado.h"


class Partido {
public: 
    Participante equipoA;
    Participante equipoB;
    Lugar lugar;
    Partido next;
    Partido sucesor;
    Vector<Resultado> modificado;
    Resultado actual;
private: 
    int id;
    QString ronda;
    int fecha;
};

#endif //_PARTIDO_H