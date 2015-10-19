/**
 * Project Pegaso
 */


#ifndef _GESTORPARTIDOS_H
#define _GESTORPARTIDOS_H

class GestorPartidos {
public: 
    
    /**
     * @param comp
     */
    void generarFixture(Competencia$ comp);
    
    /**
     * @param comp
     * @param part
     * @param res
     */
    void nuevoResultado(Competencia$ comp, Partido$ part, Resultado$ res);
    
    /**
     * @param part
     * @param comp
     */
    bool puedeModificar(Partido$ part, Competencia$ comp);
private: 
    
    /**
     * @param comp
     */
    void generarFixtureLiga(Competencia$ comp);
    
    /**
     * @param comp
     */
    void generarFixtureElimSimple(Competencia$ comp);
    
    /**
     * @param comp
     */
    void generarFixtureElimDoble(Competencia$ comp);
};

#endif //_GESTORPARTIDOS_H