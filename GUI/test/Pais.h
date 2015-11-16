/**
 * Project Pegaso
 */


#ifndef _PAIS_H
#define _PAIS_H

#include "Provincia.h"
#include <QVector>

class Provincia;
class Pais {

public: 

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);


    QVector<Provincia*> getProvincias() const;
    void setProvincias(const QVector<Provincia*> &value);

private:

    QVector<Provincia*> provincias;

    int id;

    QString nombre;

};

#endif //_PAIS_H
