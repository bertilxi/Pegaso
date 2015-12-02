#ifndef TIPORESULTADO_H
#define TIPORESULTADO_H

#include <QString>

class TipoResultado
{
public:

    int getId() const;

    void setId(int value);

    QString getNombre() const;

    void setNombre(const QString &value);

private:

    int id;

    //"Resultado Final", "Por Puntos", o "Por Sets"
    QString nombre;

};

#endif // TIPORESULTADO_H
