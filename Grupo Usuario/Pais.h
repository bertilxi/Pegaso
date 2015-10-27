/**
 * Project Pegaso
 */


#ifndef _PAIS_H
#define _PAIS_H

#include "Provincia.h"


class Pais {
public: 
	Vector<Provincia> getProvincias();
	int getId();
	QString getNombre();

private: 
    Vector<Provincia> provincias;
    int id;
    QString nombre;
};

#endif //_PAIS_H