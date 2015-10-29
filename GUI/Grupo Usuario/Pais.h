/**
 * Project Pegaso
 */


#ifndef _PAIS_H
#define _PAIS_H

#include "Provincia.h"


class Pais {
public: 

    Vector<Provincia> getProvincias() const;
    void setProvincias(const Vector<Provincia> &value);

    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

private:
    Vector<Provincia> provincias;
    int id;
    QString nombre;
};

#endif //_PAIS_H
