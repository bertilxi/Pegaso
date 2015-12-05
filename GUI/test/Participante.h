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

    QString getTable();

    QVector<Atributo> getAtributos() const;

    Participante();

    ~Participante();


private:

    int id;

    QString nombre;

    QString correo;

    QString img;

    QVector<HistorialParticipante *> historial;

    Puntaje* puntaje;
};

#endif //_PARTICIPANTE_H
