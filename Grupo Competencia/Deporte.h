/**
 * Project Pegaso
 */


#ifndef _DEPORTE_H
#define _DEPORTE_H

#include <QString>
class Deporte {
public:
    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

private:
    int id;
    QString nombre;
};

#endif //_DEPORTE_H
