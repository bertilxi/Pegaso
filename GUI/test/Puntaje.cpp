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
void Puntaje::restar(Resultado *res,Modalidad *mod,QString equipo) {

    Res* resultado;
    if(equipo=="EquipoA"){
        resultado = res->getResultadoA();
    }
    else resultado = res->getResultadoB();

    //Actualizo los puntos según el resultado del equipo
    if(resultado->getNombre()=="Ganó"){
        puntos -= mod->getPuntos_ganar();
        PG--;
    }
    if(resultado->getNombre()=="Empató"){
        puntos-=mod->getPuntos_empate();
        PE--;
    }
    if(resultado->getNombre() == "Perdió" || resultado->getNombre() == "No se presentó"){
        PP--;
    }

    //Si se presentó le descuento los puntos por presentarse
    if(resultado->getNombre() != "No se presentó"){
        puntos -= mod->getPuntos_presentarse();
    }

    //Si el tipo de resultado es por puntos descuento los tantos a favor y en contra y calculo la diferencia
    if(mod->getTipoRes()->getNombre()=="Por Puntos"){
        if(equipo=="EquipoA"){
            TF-=res->getPuntosA();
            TC-=res->getPuntosB();
        }
        else {
            TF-=res->getPuntosB();
            TC-=res->getPuntosA();
        }
        Dif=TF-TC;
    }
}

/**
 * @param part
 */
void Puntaje::sumar(Resultado *res,Modalidad *mod,QString equipo) {

    Res* resultado;
    if(equipo=="EquipoA"){
        resultado = res->getResultadoA();
    }
    else resultado = res->getResultadoB();

    //Actualizo los puntos según el resultado del equipo
    if(resultado->getNombre() =="Ganó"){
        puntos+=mod->getPuntos_ganar();
        PG++;
    }
    if(resultado->getNombre()=="Empató"){
        puntos+=mod->getPuntos_empate();
        PE++;
    }
    if(resultado->getNombre()=="Perdió" || resultado->getNombre()=="No se presentó"){
        PP++;
    }

    //Si se presentó le agrego los puntos por presentarse
    if(resultado->getNombre() != "No se presentó"){
        puntos += mod->getPuntos_presentarse();
    }

    //Si el tipo de resultado es por puntos agrego los tantos a favor y en contra y calculo la diferencia
    if(mod->getTipoRes()->getNombre()=="Por Puntos"){
        if(equipo=="EquipoA"){
            TF+=res->getPuntosA();
            TC+=res->getPuntosB();
        }
        else {
            TF+=res->getPuntosB();
            TC+=res->getPuntosA();
        }
        Dif=TF-TC;
    }
}
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
    if(other.getPG()!=PG){
        qDebug()<<"PG: "<<other.getPG()<<" "<<PG<<" en puntaje";
        return 0;
    }
    if(other.getPP()!=PP){
        qDebug()<<"PP: "<<other.getPP()<<" "<<PP<<" en puntaje";
        return 0;
    }
    if(other.getPuntos()!=puntos){
        qDebug()<<"Puntos: "<<other.getPuntos()<<" "<<puntos<<" en puntaje";
        return 0;
    }
    if(other.getTC()!=TC){
        qDebug()<<"TC: "<<other.getTC()<<" "<<TC<<" en puntaje";
        return 0;
    }
    if(other.getTF()!=TF){
        qDebug()<<"TF: "<<other.getTF()<<" "<<TF<<" en puntaje";
        return 0;
    }
    return 1;
}

Puntaje::Puntaje()
{
    puntos = 0 ;
    PG = 0 ;
    PE = 0 ;
    PP = 0 ;
    TF = 0 ;
    TC = 0 ;
    Dif = 0 ;
//    id = -1;
}






