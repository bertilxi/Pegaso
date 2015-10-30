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
    void eliminarFixture(Competencia *comp);
public:
    GestorCompetencias(GestorBaseDatos* gestb,GestorPartidos* gestp,GestorUsuarios* gestu)
        :gestorBaseDatos(gestb),gestorPartidos(gestp),gestorUsuarios(gestu){};

    /**
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     * @param operacionExitosa true si es exitosa, false e.o.c.
     */

    virtual Competencia *crearCompetencia(DtoCompetencia* datos,bool operacionExitosa,QString &error);

    /**
     * @param comp
     */
    virtual void bajaCompetencia(Competencia* comp);
    
    /**
     * @param comp
     * @param datos
     */

    virtual void modCompetencia(Competencia* comp, DtoCompetencia* datos);

    QVector<Competencia*> virtual listarCompetencias(){}
    
    /**
     * @param comp
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */

    virtual bool altaParticipante(Competencia* comp, DtoParticipante* datos, QString &error);

    /**
     * @param comp
     * @param part
     */
    virtual void eliminarParticipante(Competencia* comp, Participante* part);
    
    /**
     * @param part
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */

    virtual void modParticipante(Competencia *comp,Participante* part, DtoParticipante* datos, QString &error);

    /**
     * @param comp
     * @param part
     * @param res
     */

    virtual void nuevoResultado(Competencia* comp, Partido* part, Resultado* res);
  
    /**
     * @param id_comp
     */
    virtual Competencia *getCompetenciaFull(int id_comp);
    
    /**
     * @param id_usuario
     * @param filtros
     */
    virtual QVector<Competencia*> getCompetenciasLazy(DtoGetCompetencia*);
    
    /**
     * @param comp
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
    virtual void generarFixture(Competencia* comp,QString error);
    
    /**
     * @param part
     * @param comp
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
    virtual bool puedeModificar(Partido* part, Competencia* comp, QString &error);
};

#endif //_GESTORCOMPETENCIAS_H
