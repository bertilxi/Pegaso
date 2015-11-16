/**
 * Project Pegaso
 */


#ifndef _GESTORPARTIDOS_H
#define _GESTORPARTIDOS_H
#include "Competencia.h"
#include "Puntaje.h"
#include "Partido.h"
#include "Resultado.h"

class GestorPartidos {
public: 
    
    virtual void generarFixture(Competencia *comp);
    
    virtual void nuevoResultado(Competencia *comp, Partido *part, Resultado *res);

    virtual bool puedeModificar(Partido *part, Competencia *comp, QString &error);

    GestorPartidos(QVector<Res*> ressP): ress(ressP) {}


private:

    QVector<Res*> ress;

    Res *buscarRes(QString res);

    virtual void generarFixtureLiga(Competencia *comp);
    
    virtual void generarFixtureElimSimple(Competencia *comp);

    virtual void generarFixtureElimDoble(Competencia *comp);
};

#endif //_GESTORPARTIDOS_H
