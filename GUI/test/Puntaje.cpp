/**
 * Project Pegaso
 */


#include "Puntaje.h"


/**
 * Puntaje implementation
 */


/**
 * @param part
 */
//void Puntaje::restar(Partido part) {

//}

/**
 * @param part
 */
//void Puntaje::sumar(Partido part) {

//}
int Puntaje::getPuntos() const
{
    return puntos;
}

void Puntaje::setPuntos(int value)
{
    puntos = value;
}
int Puntaje::getPG() const
{
    return PG;
}

void Puntaje::setPG(int value)
{
    PG = value;
}
int Puntaje::getPE() const
{
    return PE;
}

void Puntaje::setPE(int value)
{
    PE = value;
}
int Puntaje::getPP() const
{
    return PP;
}

void Puntaje::setPP(int value)
{
    PP = value;
}
int Puntaje::getTF() const
{
    return TF;
}

void Puntaje::setTF(int value)
{
    TF = value;
}
int Puntaje::getTC() const
{
    return TC;
}

void Puntaje::setTC(int value)
{
    TC = value;
}
int Puntaje::getDif() const
{
    return Dif;
}

void Puntaje::setDif(int value)
{
    Dif = value;
}

bool Puntaje::operator==(const Puntaje &other) const
{
    if(other.getDif()!=Dif){
        qDebug()<<"Dif: "<<other.getDif()<<" "<<Dif<<" en puntaje";
        return 0;
    }
    if(other.getPE()!=PE){
        qDebug()<<"PE: "<<other.getPE()<<" "<<PE<<" en puntaje";
        return 0;
    }
//    if(other.getPG()!=){
//        qDebug()<<"PG: "<<other.getPG()<<" "<<PG<<" en puntaje";
//        return 0;
//    }
//    if(other.getPP()!=){
//        qDebug()<<"PP: "<<other.getPP()<<" "<<PP<<" en puntaje";
//        return 0;
//    }
//    if(other.getPuntos()!=){
//        qDebug()<<"Puntos: "<<other.getPuntos()<<" "<<Puntos<<" en puntaje";
//        return 0;
//    }
//    if(other.getTC()!=){
//        qDebug()<<"TC: "<<other.getTC()<<" "<<TC<<" en puntaje";
//        return 0;
//    }
//    if(other.getTF()!=){
//        qDebug()<<"TF: "<<other.getTF()<<" "<<TF<<" en puntaje";
//        return 0;
//    }
    return 1;
}






