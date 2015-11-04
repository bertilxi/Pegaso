#ifndef ESTADO_H
#define ESTADO_H

#include <QString>

class Estado
{
public:
    int getId() ;
    void setId(int value);
    QString getNombre() ;
    void setNombre(const QString &value);

private:
    int id;
    QString nombre;

};

#endif // ESTADO_H
