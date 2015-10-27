/**
 * Project Pegaso
 */


#ifndef _LOCALIDAD_H
#define _LOCALIDAD_H

class Localidad {
public:
	int getId();
	QString getNombre();
private: 
    int id;
    QString nombre;
};

#endif //_LOCALIDAD_H