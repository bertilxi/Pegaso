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
#include <QVector>
#include "Pais.h"
#include "Provincia.h"

class GestorUsuarios {
public:
    bool altaUsuario(DtoUsuario* datos, QString &error);
    void virtual modUsuario(Usuario* usuario, DtoUsuario* datos);
    
    Usuario *login(QString email, QByteArray password);
    Usuario* getActual() const;
    void setActual( Usuario* value);
    QVector<Provincia*> getProvincias(Pais* pais);
    QVector<Localidad*> getLocalidades(Provincia* provincia);
    GestorUsuarios(GestorBaseDatos* gestorDBP):
        gestorDB(gestorDBP) {}
private:
    Usuario* actual;
    GestorBaseDatos* gestorDB;
};

#endif //_GESTORUSUARIOS_H
