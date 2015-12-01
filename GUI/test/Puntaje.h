/**
 * Project Pegaso
 */

#ifndef _PUNTAJE_H
#define _PUNTAJE_H

#include <QDebug>
#include "Resultado.h"
#include "Puntos.h"
#include "Sets.h"
#include "Modalidad.h"

class Puntaje {
public: 
    
    void restar(Resultado *res,Modalidad *mod,QString equipo);
    
    void sumar(Resultado *res, Modalidad *mod,QString equipo);

    int getPuntos() const;

    void setPuntos(int value);

    int getPG() const;

    void setPG(int value);

    int getPE() const;

    void setPE(int value);

    int getPP() const;

    void setPP(int value);

    int getTF() const;

    void setTF(int value);

    int getTC() const;

    void setTC(int value);

    int getDif() const;

    void setDif(int value);

    bool operator==(const Puntaje &other)const;

    Puntaje();


private:

//    int id;

    int puntos;

    int PG;

    int PE;

    int PP;

    int TF;

    int TC;

    int Dif;

};

#endif //_PUNTAJE_H
