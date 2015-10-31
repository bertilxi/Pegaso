/**
 * Project Pegaso
 */


#ifndef _SET_H
#define _SET_H

#include <QDebug>
#include "Atributo.h"

class Set {
public:

    void setId(int value) {/*no hacer nada*/}

    int getNro_set() const;
    void setNro_set(int value);

    int getPuntosA() const;
    void setPuntosA(int value);

    int getPuntosB() const;
    void setPuntosB(int value);

    bool operator==(const Set &other)const;

    QString getTable() const;


    /**
     * @brief getAtributos
     * @return una lista de los atributos de Set con el correspondiente nombre
     * de sus columnas en la tabla Sets de la Base de Datos. Los atributos
     * retornados han sido casteados a QString's.
     */
    QVector<Atributo> getAtributos() const;

private:
    int nro_set;
    int puntosA;
    int puntosB;
};

#endif //_SET_H
