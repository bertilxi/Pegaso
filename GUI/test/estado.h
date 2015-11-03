#ifndef ESTADO_H
#define ESTADO_H

#include <QString>

class Estado
{
public:
    int getId() const;
    void setId(int value);
    QString getNombre() const;
    void setNombre(const QString &value);

private:
    int id;
    QString nombre;

};

#endif // ESTADO_H
