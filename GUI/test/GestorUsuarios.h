/**
 * Project Pegaso
 */


#ifndef _GESTORUSUARIOS_H
#define _GESTORUSUARIOS_H

#include "Usuario.h"
#include "GestorBaseDatos.h"
#include "dtos.h"
#include <QString>
#include <string>
#include <QDateTime>
#include <QByteArray>
#include <QCryptographicHash>
#include <QHostInfo> //Incluir QT+=network en el .pro
class GestorUsuarios {
public: 
    /**
     * @param datos
     */
    bool altaUsuario(DtoUsuario* datos, QString &error);
    
    /**
     * @param usuario
     * @param datos
     */
    void virtual modUsuario(Usuario* usuario, DtoUsuario* datos);
    
    /**
     * @param email
     * @param password
     */
    Usuario *login(QString email, QByteArray password);
    Usuario* getActual() const;
    void setActual( Usuario* value);
    GestorUsuarios(GestorBaseDatos* gestorDBP):
        gestorDB(gestorDBP) {}
private:
    Usuario* actual;
    GestorBaseDatos* gestorDB;
};

#endif //_GESTORUSUARIOS_H
