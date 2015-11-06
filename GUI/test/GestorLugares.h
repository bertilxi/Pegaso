/**
 * Project Pegaso
 */


#ifndef _GESTORLUGARES_H
#define _GESTORLUGARES_H

#include "Lugar.h"
#include "GestorBaseDatos.h"
#include "GestorUsuarios.h"
#include "dtos.h"

class GestorLugares {
public: 

    void virtual altaLugar( DtoLugar  Datos);
    void virtual bajaLugar(Lugar lugar);
    void virtual modLugar(Lugar lugar, DtoLugar datos);
    GestorLugares(GestorBaseDatos* gestorDBP, GestorUsuarios* gestorUsuariosP):
        gestorDB(gestorDBP), gestorUsuarios(gestorUsuariosP) {}
    QVector<Lugar *> getLugares();

private:
    GestorBaseDatos* gestorDB;
    GestorUsuarios* gestorUsuarios;

};

#endif //_GESTORLUGARES_H
