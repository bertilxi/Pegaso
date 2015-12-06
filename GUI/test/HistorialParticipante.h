/**
 * Project Pegaso
 */


#ifndef _HISTORIALPARTICIPANTE_H
#define _HISTORIALPARTICIPANTE_H

#include <QString>
#include <QDebug>
#include "Atributo.h"

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

    bool operator==(const HistorialParticipante &other)const;

    QString getTable();

    QVector<Atributo> getAtributos() const;

    HistorialParticipante();


private:

    int id;

    QString nombre;

    QString correo;

    QString imagen;

};

#endif //_HISTORIALPARTICIPANTE_H
