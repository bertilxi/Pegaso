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
#include <QHostInfo>
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

    GestorUsuarios  (GestorBaseDatos* gestorDBP):
                    gestorDB(gestorDBP) {}


private:

    Usuario* actual;

    QVector<Pais *> paises;

    QVector<Provincia *> provincias;

    GestorBaseDatos* gestorDB;
};

#endif //_GESTORUSUARIOS_H
