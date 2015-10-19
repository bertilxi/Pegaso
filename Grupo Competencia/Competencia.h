/**
 * Project Pegaso
 */


#ifndef _COMPETENCIA_H
#define _COMPETENCIA_H

#include "Disponibilidad.h"
#include "Participante.h"
#include "Modalidad.h"
#include "Partido.h"
#include "Deporte.h"


class Competencia {
public: 
    Vector<Disponibilidad> disponibilidades;
    Vector<Participante> participantes;
    Modalidad modalidad;
    Vector<Partido> partidos;
    Deporte deporte;
private: 
    int id;
    QString estado;
    QString nombre;
};

#endif //_COMPETENCIA_H