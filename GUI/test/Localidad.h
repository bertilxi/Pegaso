/**
 * Project Pegaso
 */


#ifndef _LOCALIDAD_H
#define _LOCALIDAD_H
#include <QString>
#include "Provincia.h"

class Provincia;
class Localidad {

public:

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);

    Provincia *getProvincia() const;

    void setProvincia(Provincia *value);

private:

    int id;

    QString nombre;

    Provincia * provincia;

};

#endif //_LOCALIDAD_H
