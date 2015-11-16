/**
 * Project Pegaso
 */


#ifndef _PROVINCIA_H
#define _PROVINCIA_H

#include "Localidad.h"
#include <QString>
 #include <QVector>


class Provincia {

public: 

    QVector<Localidad> getLocalidades() const;

    void setLocalidades(const QVector<Localidad> &value);

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);


private:

    QVector<Localidad> localidades;

    int id;

    QString nombre;
};

#endif //_PROVINCIA_H
