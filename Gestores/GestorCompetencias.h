/**
 * Project Pegaso
 */


#ifndef _GESTORCOMPETENCIAS_H
#define _GESTORCOMPETENCIAS_H

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

class GestorCompetencias {
public: 
    
    /**
     * @param datos
     */
    Competencia virtual crearCompetencia(Datos datos);
    
    /**
     * @param comp
     */
    bool virtual bajaCompetencia(Competencia comp);
    
    /**
     * @param comp
     * @param datos
     */
    bool virtual modCompetencia(Competencia comp, Datos datos);
    
    QVector<Competencia> virtual listarCompetencias();
    
    /**
     * @param comp
     * @param datos
     */
    bool virtual altaParticipante(Competencia comp, Datos datos);
    
    /**
     * @param comp
     * @param part
     */
    bool virtual eliminarParticipante(Competencia comp, Partido part);
    
    /**
     * @param part
     * @param datos
     */
    bool virtual modParticipante(Participante part, Datos datos);
    
    /**
     * @param comp
     * @param part
     * @param res
     */
    void virtual nuevoResultado(Competencia comp, Partido$ part, Resultado res);
    
    /**
     * @param id_comp
     */
    Competencia virtual getCompetenciaFull(int id_comp);
    
    /**
     * @param id_usuario
     * @param filtros
     */
    QVector<Competencia> virtual getCompetenciasLazy(int id_usuario, QVector<QString> filtros);
    
    /**
     * @param comp
     */
    bool virtual generarFixture(Competencia comp);
    
    /**
     * @param part
     * @param comp
     */
    bool virtual puedeModificar(Partido part, Competencia comp);
};

#endif //_GESTORCOMPETENCIAS_H
