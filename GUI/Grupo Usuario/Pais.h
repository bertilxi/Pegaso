/**
 * Project Pegaso
 */


#ifndef _PAIS_H
#define _PAIS_H

#include "Provincia.h"


class Pais {
public: 
    Vector<Provincia> provincias;
private: 
    int id;
    QString nombre;
};

#endif //_PAIS_H