#ifndef RES_H
#define RES_H

#include <QString>

class Res
{
public:

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);

    Res();

private:

    int id;

    // ganó, perdió, empató, no se presentó
    QString nombre;
};

#endif // RES_H
