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
    Vector<Competencia> competencias;
    Vector<Lugar> lugares;
    Doc doc;
    Localidad localidad;
    Vector<Auditoria> auditorias;
private: 
    int id;
    QString password;
    QString nombre;
    QString apellido;
    QString email;
    int nro_doc;
};

#endif //_USUARIO_H
