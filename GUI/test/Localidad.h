/**
 * Project Pegaso
 */


#ifndef _LOCALIDAD_H
#define _LOCALIDAD_H

#include <QString>

class Localidad {
public:

    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

private:
    int id;
    QString nombre;
};

#endif //_LOCALIDAD_H
