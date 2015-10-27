/**
 * Project Pegaso
 */


#ifndef _GESTORLUGARES_H
#define _GESTORLUGARES_H

#include "../Grupo Competencia/Lugar.h"
#include "dtos.h"

class GestorLugares {
public: 
    
    /**
     * @param datos
     * @param Datos
     */
    void virtual altaLugar( DtoLugar  Datos);
    
    /**
     * @param lugar
     */
    void virtual bajaLugar(Lugar lugar);
    
    /**
     * @param lugar
     * @param datos
     */
    void virtual modLugar(Lugar lugar, DtoLugar datos);
};

#endif //_GESTORLUGARES_H
