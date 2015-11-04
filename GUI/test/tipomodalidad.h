#ifndef TIPOMODALIDAD_H
#define TIPOMODALIDAD_H

#include <QString>

class TipoModalidad
{
private:
    int id;
    QString nombre;
public:

    int getId() ;
    void setId(int value);
    QString getNombre() ;
    void setNombre(const QString &value);
};

#endif // TIPOMODALIDAD_H
