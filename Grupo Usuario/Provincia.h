/**
 * Project Pegaso
 */


#ifndef _PROVINCIA_H
#define _PROVINCIA_H

#include "Localidad.h"


class Provincia {
public: 

    Vector<Localidad> getLocalidades() const;
    void setLocalidades(const Vector<Localidad> &value);

    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

private:
    Vector<Localidad> localidades;
    int id;
    QString nombre;
};

#endif //_PROVINCIA_H
