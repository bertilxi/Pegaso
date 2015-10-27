/**
 * Project Pegaso
 */


#ifndef _GESTORPARTICIPANTES_H
#define _GESTORPARTICIPANTES_H

#include "GestorBaseDatos.h"

class GestorParticipantes {
public: 
    
    void virtual alta();
    
    void virtual baja();
    
    void mod();
    
    void actualizarHistorial();
    
    void listar();
    
    void mod_puntos();
    GestorParticipantes(GestorBaseDatos* gestorDBP):
        gestorDB(gestorDBP) {}
private:
    GestorBaseDatos* gestorDB;
};

#endif //_GESTORPARTICIPANTES_H
