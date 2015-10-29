/**
 * Project Pegaso
 */

#include <QVector>
#include "../Grupo Competencia/Competencia.h"
#include "dtos.h"


#ifndef _GESTORBASEDATOS_H
#define _GESTORBASEDATOS_H

class GestorBaseDatos {
public: 
    
    /**
     * @param obj
     * @param id
     * @brief Carga un objeto haciendo una consulta con el id en la tabla correspondiente
     */
    template <class T>
    T load(T obj, int id);
    
    /**
     * @brief guarda una lista de objetos
     * @param objptrs punteros a objetos
     * @param tabla nombre de la tabla de la BD donde guardar los objetos
     * @param id_externo es un puntero a un atributo correspondiente a una fk.
     * Su valor es NULL si no se la llama con tal argumento.
     * @return true si tuvo exito, false si fallo
     */
    template <class T1>
    bool save(QVector<T1 *> objptrs, Atributo *id_externo = NULL);

    /**
     * @brief persiste un objeto Competencia
     * @param comp la competencia a persistir
     * @return true si tuvo exito, false si fallo
     */
    bool saveCompetencia(Competencia *comp, Atributo usuarioId);
    //implementado en libreria "GestorBaseDatosSaveEspeciales.h"

    bool saveResultado(Resultado *resultado, Atributo partidoId);
    //implementado en libreria "GestorBaseDatosSaveEspeciales.h"

    
    /**
     * @param obj1
     * @param obj2
     * @brief Guarda una relacion n a n entre dos objetos
     *
     * obj1 debe conocer la tabla de la relacion
     */
    template <class T2,class T3>
    bool saveRelacion(T2 *obj1, T3 *obj2);
    
    /**
     * @param obj
     * @param filtros
     * @brief Ejecuta una consulta en la base de datos con filtros como parametros en select
     */
    template <class T4>
    QVector<T4> query(T4 obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();

private:

    /**
     * @brief utiliza el nombre de una tabla y conjuntos columna-valor (atributos)
     * para armar un insert SQL y ejecutarlo en la BD.
     * @param tabla
     * @param atributos
     * @return id del objeto que se acaba de guardar, asignado por la BD
     */
    int armarQuery(QString tabla, const QVector<Atributo> &atributos);
};

#include "GestorBaseDatosSaveEspeciales.h"

#endif //_GESTORBASEDATOS_H
