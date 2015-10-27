/**
 * Project Pegaso
 */


#include "Usuario.h"

/**
 * Usuario implementation
 */
QString Usuario::getNombre(){ return nombre;}

QString Usuario::getPassword(){return password;}

QString Usuario::getApellido(){return apellido;}

QString Usuario::getEmail(){return email;}

int Usuario::getNroDoc(){return nro_doc;}

QVector<Competencia> Usuario::getCompetencias(){return competencias;}

Doc Usuario::getDoc(){return doc;}

Localidad Usuario::getLocalidad(){return localidad;}

QVector<Auditoria> Usuario::getAuditorias(){return auditorias;}

QVector<Lugar> Usuario::getLugares(){return lugares;}