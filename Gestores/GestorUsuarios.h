/**
 * Project Pegaso
 */


#ifndef _GESTORUSUARIOS_H
#define _GESTORUSUARIOS_H

#include "../Grupo Usuario/Usuario.h"


class GestorUsuarios {
public: 
    /**
     * @param datos
     */
    void virtual altaUsuario(Datos datos);
    
    /**
     * @param usuario
     * @param datos
     */
    void virtual modUsuario(Usuario usuario, Datos datos);
    
    /**
     * @param email
     * @param password
     */
    Usuario virtual login(QString email, QString password);
    Usuario getActual() const;
    void setActual(const Usuario &value);
private:
    Usuario actual;
};

#endif //_GESTORUSUARIOS_H
