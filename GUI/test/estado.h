#ifndef ESTADO_H
#define ESTADO_H

#include <QString>

class Estado
{
public:
    QString getNombre() ;
    void setNombre(const QString &value);
    int getId() const;
    void setId(int value);

private:
    int id;
    QString nombre;

};

#endif // ESTADO_H
