/**
 * Project Pegaso
 */


#ifndef _MODALIDAD_H
#define _MODALIDAD_H

#include <QString>
#include <QDebug>
#include <QVector>
#include "Atributo.h"

class Modalidad {
public:
    int getId() const;
    void setId(int value);


    QString getNombre() const;
    void setNombre(const QString &value);


    QString getTipo_resultado() const;
    void setTipo_resultado(const QString &value);

    int getCant_max_sets() const;
    void setCant_max_sets(int value);

    int getPuntos_presentarse() const;
    void setPuntos_presentarse(int value);

    int getPuntos_ganar() const;
    void setPuntos_ganar(int value);

    bool getEmpate() const;
    void setEmpate(bool value);

    int getPuntos_empate() const;
    void setPuntos_empate(int value);

    bool operator==(const Modalidad &other)const;

    QString getTable();

    /**
     * @brief getAtributos
     * @return una lista de los atributos de Modalidad con el correspondiente nombre
     * de sus columnas en la tabla Modalidad de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

    int getId_nombre() const;
    void setId_nombre(int value);

    int getId_tipo_resultado() const;
    void setId_tipo_resultado(int value);

private:
    int id;
    int id_nombre; ///de otra forma debo hacer una consulta por el id de nombre
    QString nombre;
    int id_tipo_resultado; ///de otra forma debo hacer una consulta por el id de tipo_resultado
    //"Resultado", "Puntos", o "Sets"
    QString tipo_resultado;
    int cant_max_sets;
    int puntos_presentarse;
    int puntos_ganar;
    bool empate;
    int puntos_empate;
};

#endif //_MODALIDAD_H
