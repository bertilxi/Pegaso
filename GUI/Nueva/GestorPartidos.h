/**
 * Project Pegaso
 */


#ifndef _GESTORPARTIDOS_H
#define _GESTORPARTIDOS_H

#include "GestorBaseDatos.h"
#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Modalidad.h"
#include "../Grupo Competencia/Disponibilidad.h"
#include "../Grupo Competencia/Partido.h"


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

    GestorPartidos(GestorBaseDatos* gestorDBP): gestorDB(gestorDBP) {}

private:
    GestorBaseDatos* gestorDB;
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
