/**
 * Project Pegaso
 */


#ifndef _USUARIO_H
#define _USUARIO_H

#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Lugar.h"
#include "Doc.h"
#include "Localidad.h"
#include "Auditoria.h"


class Usuario {
public: 
    QString getNombre();
    QString getPassword();
    QString getApellido();
    QString getEmail();
    int getNroDoc();
    QVector<Competencia> getCompetencias();
    QVector<Lugar> getLugares();
    Doc getDoc();
    Localidad getLocalidad();
    QVector<Auditoria> getAuditorias();
private: 
    int id;
    QString password;
    QString nombre;
    QString apellido;
    QString email;
    int nro_doc;
    QVector<Competencia> competencias;
    QVector<Lugar> lugares;
    Doc doc;
    Localidad localidad;
    QVector<Auditoria> auditorias;
};

#endif //_USUARIO_H
