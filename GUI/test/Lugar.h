/**
 * Project Pegaso
 */


#ifndef _LUGAR_H
#define _LUGAR_H

#include <QString>
#include <QDebug>

class Lugar {

public:

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);

    QString getDescripcion() const;

    void setDescripcion(const QString &value);

    bool operator==(const Lugar &other)const;


private:

    int id;

    QString nombre;

    QString descripcion;
};

#endif //_LUGAR_H
