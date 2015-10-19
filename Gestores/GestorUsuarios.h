/**
 * Project Pegaso
 */


#ifndef _GESTORUSUARIOS_H
#define _GESTORUSUARIOS_H

#include "Usuario.h"


class GestorUsuarios {
public: 
    Usuario actual;
    
    /**
     * @param datos
     */
    void altaUsuario(Datos datos);
    
    /**
     * @param usuario
     * @param datos
     */
    void modUsuario(Usuario$ usuario, Datos datos);
    
    /**
     * @param email
     * @param password
     */
    Usuario$ login(QString email, QString password);
};

#endif //_GESTORUSUARIOS_H