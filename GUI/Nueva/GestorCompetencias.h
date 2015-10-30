/**
 * Project Pegaso
 */


#ifndef _GESTORCOMPETENCIAS_H
#define _GESTORCOMPETENCIAS_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <Qt>
#include "GestorPartidos.h"
#include "GestorBaseDatos.h"
#include "GestorUsuarios.h"
#include "dtos.h"


class GestorCompetencias {
private:
    GestorPartidos* gestorPartidos;
    GestorBaseDatos* gestorBaseDatos;
    GestorUsuarios* gestorUsuarios;
    void eliminarFixture(Competencia *comp);
public:
    GestorCompetencias(GestorBaseDatos* gestb,GestorPartidos* gestp,GestorUsuarios* gestu)
        :gestorBaseDatos(gestb),gestorPartidos(gestp),gestorUsuarios(gestu){};


};

#endif //_GESTORCOMPETENCIAS_H
