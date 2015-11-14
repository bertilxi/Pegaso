/**
 * Project Pegaso
 */


#ifndef _GESTORLUGARES_H
#define _GESTORLUGARES_H

#include "Lugar.h"
#include "GestorBaseDatos.h"
#include "dtos.h"
#include "GestorUsuarios.h"

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
    GestorLugares(GestorBaseDatos* gestorDBP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorUsuarios(gestorUsuariosP) {}
    QVector<Lugar *> getLugares();
private:
    GestorBaseDatos* gestorDB;
    GestorUsuarios* gestorUsuarios;
};

#endif //_GESTORLUGARES_H
