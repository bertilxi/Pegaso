/**
 * Project Pegaso
 */


#ifndef _GESTORLUGARES_H
#define _GESTORLUGARES_H

#include "../Grupo Competencia/Lugar.h"

class GestorLugares {
public: 
    
    /**
     * @param datos
     * @param Datos
     */
    void virtual altaLugar( datos,  Datos);
    
    /**
     * @param lugar
     */
    void virtual bajaLugar(Lugar lugar);
    
    /**
     * @param lugar
     * @param datos
     */
    void virtual modLugar(Lugar lugar, Datos datos);
};

#endif //_GESTORLUGARES_H
