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
    
    /**
     * @param comp
     */
    virtual void generarFixture(Competencia *comp);
    
    /**
     * @param comp
     * @param part
     * @param res
     */
    virtual void nuevoResultado(Competencia *comp, Partido *part, Resultado *res);
    
    /**
     * @param part
     * @param comp
     */

    virtual bool puedeModificar(Partido *part, Competencia *comp, QString &error);

    GestorPartidos(QVector<Res*> ressP): ress(ressP) {}

private:
    QVector<Res*> ress;
    Res *buscarRes(QString res);
    /**
     * @param comp
     */
    virtual void generarFixtureLiga(Competencia *comp);
    
    /**
     * @param comp
     */
    virtual void generarFixtureElimSimple(Competencia *comp);
    
    /**
     * @param comp
     */
    virtual void generarFixtureElimDoble(Competencia *comp);
};

#endif //_GESTORPARTIDOS_H
