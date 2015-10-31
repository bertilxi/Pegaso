/**
 * Project Pegaso
 */


#ifndef _PARTIDO_H
#define _PARTIDO_H

#include <QDebug>
#include "Participante.h"
#include "Lugar.h"
#include "Resultado.h"

class Participante;

class Partido {
public: 

    int getId() const;
    void setId(int value);

    QString getRonda() const;
    void setRonda(const QString &value);

    int getFecha() const;
    void setFecha(int value);

    Participante *getEquipoA() const;
    void setEquipoA(Participante *value);

    Participante *getEquipoB() const;
    void setEquipoB(Participante *value);

    Lugar *getLugar() const;
    void setLugar(Lugar *value);

    QVector<Resultado *> getModificado() const;
    void setModificado(const QVector<Resultado *> &value);

    Resultado *getActual() const;
    void setActual( Resultado *value);

    bool operator==(const Partido &other)const;

    QString getTable() const;

    QString getTable(Partido &sucesor) const;

    /**
     * @brief getAtributos
     * @return una lista de los atributos de Partido con el correspondiente nombre
     * de sus columnas en la tabla Partido de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

    QVector<Atributo> getAtributos(const Partido &sucesor) const;

    QVector<Partido *> getSucesores() const;
    void setSucesores(const QVector<Partido *> &value);

private:
    int id;
    QString ronda;
    int fecha;
    Participante *equipoA;
    Participante *equipoB;
    Lugar *lugar;
    QVector<Partido *> sucesores;
    QVector<Resultado *> modificado;
    Resultado *actual;
};

#endif //_PARTIDO_H