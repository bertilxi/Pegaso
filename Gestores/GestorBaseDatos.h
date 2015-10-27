/**
 * Project Pegaso
 */

#include <QVector>
#include "../Grupo Competencia/Competencia.h"


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
     * @param objs
     * @brief Guarda una lista de objetos en su correspondiente tabla
     */
    template <class T1>
    bool save(QVector<T1 *> objptrs);

    /**
     * @brief persiste un objeto Competencia
     * @param comp la competencia a persistir
     * @return true si tuvo exito, false si fallo
     */
    bool saveCompetencia(Competencia *comp, int usuarioId);
    //implementado en libreria "GestorBaseDatosSaveEspeciales.h"

    bool saveResultado(Resultado *resultado, int partidoId);
    //implementado en libreria "GestorBaseDatosSaveEspeciales.h"


    /**
     * @param objs
     * @param id
     * @brief Guarda una lista de objetos que necesitan una fk pero el objeto no la conoce 
     *
     * objs.getCampos() retorna una lista que debe incluir como ULTIMO elemento el campo
     * al que corresponde el parametro id.
     */
    template <class T2>
    bool save(QVector<T2 *> objptrs, int id);


    /**
     * @brief arma y ejecuta queries para guardar una lista de objetos
     * @param objptrs punteros a objetos
     * @param tabla nombre de la tabla de la BD donde guardar los objetos
     * @param campos nombre de los campos donde guardar los datos
     * @param valores valores de los datos a guardar
     * @return true si tuvo exito, false si fallo
     */
    template <class Ta>
    bool armarYEjecutar(QVector<Ta *> &objptrs, QString &tabla, QVector<QString> &campos, QVector<QString> &valores);

    
    /**
     * @param obj1
     * @param obj2
     * @brief Guarda una relacion n a n entre dos objetos
     *
     * obj1 debe conocer la tabla de la relacion
     */
    template <class T3,class T4>
    bool saveRelacion(T3 *obj1, T4 *obj2);
    
    /**
     * @param obj
     * @param filtros
     * @brief Ejecuta una consulta en la base de datos con filtros como parametros en select
     */
    template <class T5>
    QVector<T5> query(T5 obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();
};

#include "GestorBaseDatosSaveEspeciales.h"

#endif //_GESTORBASEDATOS_H
