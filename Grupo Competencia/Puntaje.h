/**
 * Project Pegaso
 */


#ifndef _PUNTAJE_H
#define _PUNTAJE_H

class Puntaje {
public: 
    
    /**
     * @param part
     */
    void restar(Partido$ part);
    
    /**
     * @param part
     */
    void sumar(Partido$ part);
private: 
    int puntos;
    int PG;
    int PE;
    int PP;
    int TF;
    int TC;
    int Dif;
};

#endif //_PUNTAJE_H