/**
 * Project Pegaso
 */


#ifndef _MODALIDAD_H
#define _MODALIDAD_H

class Modalidad {
private: 
    int id;
    QString nombre;
    QString tipo_resultado;
    int cant_max_sets;
    int puntos_presentarse;
    int puntos_ganar;
    bool empate;
    int puntos_empate;
};

#endif //_MODALIDAD_H