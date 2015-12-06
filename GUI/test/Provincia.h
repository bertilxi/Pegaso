/**
 * Project Pegaso
 */


#ifndef _PROVINCIA_H
#define _PROVINCIA_H

#include "Localidad.h"
#include <QString>
#include <QVector>
#include "Pais.h"

class Localidad;
class Pais;
class Provincia {

public: 

    QVector<Localidad*> getLocalidades() const;

    void setLocalidades(const QVector<Localidad*> &value);

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);

    Provincia();


private:

    QVector<Localidad*> localidades;

    int id;

    QString nombre;
};

#endif //_PROVINCIA_H
