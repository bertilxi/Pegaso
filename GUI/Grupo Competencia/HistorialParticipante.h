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

    /**
     * @brief getAtributos
     * @return una lista de los atributos de HistorialParticipante con el correspondiente nombre
     * de sus columnas en la tabla Historial_participante de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

private:
    int id;
    QString nombre;
    QString correo;
    QString imagen;
};

#endif //_HISTORIALPARTICIPANTE_H
