#ifndef TIPOMODALIDAD_H
#define TIPOMODALIDAD_H


class TipoModalidad
{
private:
    int id;
    QString nombre;
public:

    int getId() const;
    void setId(int value);
    QString getNombre() const;
    void setNombre(const QString &value);
};

#endif // TIPOMODALIDAD_H
