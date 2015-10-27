/**
 * Project Pegaso
 */


#ifndef _GESTORCOMPETENCIAS_H
#define _GESTORCOMPETENCIAS_H

#include <QString>
#include <QVector>
#include <QDateTime>
#include <Qt>
#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Modalidad.h"
#include "../Grupo Competencia/Participante.h"
#include "../Grupo Competencia/HistorialParticipante.h"
#include "../Grupo Competencia/Lugar.h"
#include "../Grupo Competencia/Deporte.h"
#include "../Grupo Competencia/Disponibilidad.h"
#include "../Grupo Competencia/Resultado.h"
#include "GestorPartidos.h"
#include "GestorBaseDatos.h"
#include "GestorUsuarios.h"
<<<<<<< HEAD
#include "../dto.cpp"
=======
#include "dtos.h"
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c

class GestorCompetencias {
public:
    GestorCompetencias(GestorBaseDatos* gestb,GestorPartidos* gestp,GestorUsuarios* gestu)
        :gestorBaseDatos(gestb),gestorPartidos(gestp),gestorUsuarios(gestu){};
    GestorPartidos* gestorPartidos;
    GestorBaseDatos* gestorBaseDatos;
    GestorUsuarios* gestorUsuarios;
    /**
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     * @param operacionExitosa true si es exitosa, false e.o.c.
     */
<<<<<<< HEAD
    virtual Competencia *crearCompetencia(DtoCompetencia* datos,bool operacionExitosa,QString error);
=======
    Competencia virtual crearCompetencia(DtoCompetencia datos);
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c
    
    /**
     * @param comp
     */
    virtual void bajaCompetencia(Competencia* comp);
    
    /**
     * @param comp
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
<<<<<<< HEAD
    virtual bool modCompetencia(Competencia* comp, DtoCompetencia* datos,QString error);
=======
    bool virtual modCompetencia(Competencia comp, DtoCompetencia datos);
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c
    
    QVector<Competencia*> virtual listarCompetencias();
    
    /**
     * @param comp
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
<<<<<<< HEAD
    virtual bool altaParticipante(Competencia* comp, DtoParticipante* datos,QString error);
=======
    bool virtual altaParticipante(Competencia comp, DtoParticipante datos);
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c
    
    /**
     * @param comp
     * @param part
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
    virtual bool eliminarParticipante(Competencia* comp, Participante* part,QString error);
    
    /**
     * @param part
     * @param datos
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
<<<<<<< HEAD
    virtual bool modParticipante(Participante* part,DtoParticipante* datos,QString error);
=======
    bool virtual modParticipante(Participante part, DtoParticipante datos);
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c
    
    /**
     * @param comp
     * @param part
     * @param res
     */
<<<<<<< HEAD
    virtual void nuevoResultado(Competencia* comp, Partido* part, Resultado* res);
=======
    void virtual nuevoResultado(Competencia comp, Partido part, Resultado res);
>>>>>>> 94e80309d220c62de72b9d2e18695f732118ce2c
    
    /**
     * @param id_comp
     */
    virtual Competencia *getCompetenciaFull(int id_comp);
    
    /**
     * @param id_usuario
     * @param filtros
     */
    virtual QVector<Competencia*> getCompetenciasLazy(DtoGetCompetencia);
    
    /**
     * @param comp
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
    virtual bool generarFixture(Competencia* comp,QString error);
    
    /**
     * @param part
     * @param comp
     * @param error informacion sobre el error ocurrido o si fue exitosa la operacion
     */
    virtual bool puedeModificar(Partido* part, Competencia* comp,QString error);
};

#endif //_GESTORCOMPETENCIAS_H
