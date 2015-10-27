/**
 * Project Pegaso
 */


#ifndef _PROVINCIA_H
#define _PROVINCIA_H

#include "Localidad.h"


class Provincia {
public: 
    Vector<Localidad> localidades;
private: 
    int id;
    QString nombre;
};

#endif //_PROVINCIA_H