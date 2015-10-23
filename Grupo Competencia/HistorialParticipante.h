/**
 * Project Pegaso
 */

#include <QString>


#ifndef _HISTORIALPARTICIPANTE_H
#define _HISTORIALPARTICIPANTE_H

class HistorialParticipante {
public:
    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

    QString getCorreo() const;
    void setCorreo(const QString &value);

    QString getImagen() const;
    void setImagen(const QString &value);

private:
    int id;
    QString nombre;
    QString correo;
    QString imagen;
};

#endif //_HISTORIALPARTICIPANTE_H
