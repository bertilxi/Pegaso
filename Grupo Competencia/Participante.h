/**
 * Project Pegaso
 */


#ifndef _PARTICIPANTE_H
#define _PARTICIPANTE_H

#include "HistorialParticipante.h"
#include "Puntaje.h"


class Participante {
public: 
    Vector<HistorialParticipante> historial;
    Puntaje puntaje;
private: 
    int id;
    QString nombre;
    QString correo;
    QString img;
};

#endif //_PARTICIPANTE_H