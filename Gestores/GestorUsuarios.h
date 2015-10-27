/**
 * Project Pegaso
 */


#ifndef _GESTORUSUARIOS_H
#define _GESTORUSUARIOS_H

#include "../Grupo Usuario/Usuario.h"
#include "GestorBaseDatos.h"
#include "dtos.h"


class GestorUsuarios {
public: 
    /**
     * @param datos
     */
    void virtual altaUsuario(DtoUsuario datos);
    
    /**
     * @param usuario
     * @param datos
     */
    void virtual modUsuario(Usuario usuario, DtoUsuario datos);
    
    /**
     * @param email
     * @param password
     */
    Usuario virtual login(QString email, QString password);
    Usuario getActual() const;
    void setActual(const Usuario &value);
    GestorUsuarios(GestorBaseDatos* gestorDBP):
        gestorDB(gestorDBP) {}
private:
    Usuario actual;
    GestorBaseDatos* gestorDB;
};

#endif //_GESTORUSUARIOS_H
