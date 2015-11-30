/**
 * Project Pegaso
 */


#ifndef _GESTORCOMPETENCIAS_H
#define _GESTORCOMPETENCIAS_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <Qt>
#include "Competencia.h"
#include "Modalidad.h"
#include "Participante.h"
#include "HistorialParticipante.h"
#include "Lugar.h"
#include "Deporte.h"
#include "Disponibilidad.h"
#include "Resultado.h"
#include "Partido.h"
#include "GestorPartidos.h"
#include "GestorBaseDatos.h"
#include "GestorUsuarios.h"
#include "dtos.h"


class GestorCompetencias {

private:

    GestorPartidos* gestorPartidos;

    GestorBaseDatos* gestorBaseDatos;

    GestorUsuarios* gestorUsuarios;

    QVector<Estado*> estados;

    void eliminarFixture(Competencia *comp);

    Estado *obtenerEstado(QString estado);


public:

    GestorCompetencias(GestorBaseDatos* gestb,GestorPartidos* gestp,GestorUsuarios* gestu,QVector<Estado*> est)
        :gestorBaseDatos(gestb),gestorPartidos(gestp),gestorUsuarios(gestu),estados(est){};

    virtual Competencia *crearCompetencia(DtoCompetencia* datos,bool operacionExitosa,QString &error);

    virtual void bajaCompetencia(Competencia* comp);

    virtual void modCompetencia(Competencia* comp, DtoCompetencia* datos);

    QVector<Competencia*> virtual listarCompetencias(DtoGetCompetencia * datos){}

    virtual bool altaParticipante(Competencia* comp, DtoParticipante* datos, QString &error);

    virtual void eliminarParticipante(Competencia* comp, Participante* part);

    virtual void modParticipante(Competencia *comp,Participante* part, DtoParticipante* datos, QString &error);

    virtual void nuevoResultado(Competencia* comp, Partido* part, Resultado* res);
  
    virtual Competencia *getCompetenciaFull(int id_comp);
    
    virtual QVector<Competencia*> getCompetenciasLazy(DtoGetCompetencia*);

    virtual bool generarFixture(Competencia* comp,QString error);

    virtual bool puedeModificar(Partido* part, Competencia* comp, QString &error);

    QVector<TipoResultado *> getTiposResultado();

};

#endif //_GESTORCOMPETENCIAS_H
