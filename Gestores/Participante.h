/**
 * Project Pegaso
 */


#ifndef _PARTICIPANTE_H
#define _PARTICIPANTE_H

#include "HistorialParticipante.h"
#include "Puntaje.h"

#include <QString>
#include <QVector>
#include <QDebug>

class Puntaje;

class Participante {
public: 

    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

    QString getCorreo() const;
    void setCorreo(const QString &value);

    QString getImg() const;
    void setImg(const QString &value);

    QVector<HistorialParticipante *> getHistorial() const;
    void setHistorial(const QVector<HistorialParticipante *> &value);

    Puntaje *getPuntaje() const;
    void setPuntaje(Puntaje *value);

    bool operator==(const Participante &other)const;

    //usado en GestorBaseDatos
    static bool LessThan(Participante *a, Participante *b);

    QString getTable();

    /**
     * @brief getAtributos
     * @return una lista de los atributos de Participante con el correspondiente nombre
     * de sus columnas en la tabla Participante de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

private:
    int id;
    QString nombre;
    QString correo;
    QString img;
    QVector<HistorialParticipante *> historial;
    Puntaje* puntaje;
};

#endif //_PARTICIPANTE_H
