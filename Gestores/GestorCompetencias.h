/**
 * Project Pegaso
 */


#ifndef _GESTORCOMPETENCIAS_H
#define _GESTORCOMPETENCIAS_H

class GestorCompetencias {
public: 
    
    /**
     * @param datos
     */
    Competencia$ crearCompetencia(Datos datos);
    
    /**
     * @param comp
     */
    bool bajaCompetencia(Competencia$ comp);
    
    /**
     * @param comp
     * @param datos
     */
    bool modCompetencia(Competencia$ comp, Datos datos);
    
    QVector<Competencia> listarCompetencias();
    
    /**
     * @param comp
     * @param datos
     */
    bool altaParticipante(Competencia$ comp, Datos datos);
    
    /**
     * @param comp
     * @param part
     */
    bool eliminarParticipante(Competencia$ comp, Partido$ part);
    
    /**
     * @param part
     * @param datos
     */
    bool modParticipante(Participante$ part, Datos datos);
    
    /**
     * @param comp
     * @param part
     * @param res
     */
    void nuevoResultado(Competencia$ comp, Partido$ part, Resultado$ res);
    
    /**
     * @param id_comp
     */
    Competencia$ getCompetenciaFull(int id_comp);
    
    /**
     * @param id_usuario
     * @param filtros
     */
    QVector<Competencia> getCompetenciasLazy(int id_usuario, QVector<QString> filtros);
    
    /**
     * @param comp
     */
    bool generarFixture(Competencia$ comp);
    
    /**
     * @param part
     * @param comp
     */
    bool puedeModificar(Partido$ part, Competencia$ comp);
};

#endif //_GESTORCOMPETENCIAS_H