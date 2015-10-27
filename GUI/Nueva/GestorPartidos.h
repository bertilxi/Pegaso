/**
 * Project Pegaso
 */


#ifndef _GESTORPARTIDOS_H
#define _GESTORPARTIDOS_H

#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Puntaje.h"
#include "../Grupo Competencia/Partido.h"
#include "../Grupo Competencia/Resultado.h"


class GestorPartidos {
public: 
    
    /**
     * @param comp
     */
    void virtual generarFixture(Competencia comp);
    
    /**
     * @param comp
     * @param part
     * @param res
     */
    void virtual nuevoResultado(Competencia comp, Partido part, Resultado res);
    
    /**
     * @param part
     * @param comp
     */
    bool virtual puedeModificar(Partido part, Competencia comp);
private: 
    
    /**
     * @param comp
     */
    void virtual generarFixtureLiga(Competencia comp);
    
    /**
     * @param comp
     */
    void virtual generarFixtureElimSimple(Competencia comp);
    
    /**
     * @param comp
     */
    void virtual generarFixtureElimDoble(Competencia comp);
};

#endif //_GESTORPARTIDOS_H
