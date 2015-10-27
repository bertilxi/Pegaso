/**
 * Project Pegaso
 */


#ifndef _PROVINCIA_H
#define _PROVINCIA_H

#include "Localidad.h"


class Provincia {
public: 
	Vector<Localidad> getLocalidades();
	int getId();
	QString getNombre();
private: 
    Vector<Localidad> localidades;
    int id;
    QString nombre;
};

#endif //_PROVINCIA_H