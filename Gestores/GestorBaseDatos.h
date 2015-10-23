/**
 * Project Pegaso
 */


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
    T virtual load(T obj, int id);
    
    /**
     * @param objs
     * @brief Guarda una lista de objetos en su correspondiente tabla
     */
    template <class T1>
    void virtual save(QVector<T1> objs);
    
    /**
     * @param objs
     * @param id
     * @brief Guarda una lista de objetos que necesitan una fk pero el objeto no la conoce 
     */
    template <class T2>
    void virtual save(QVector<T2> objs, int id);
    
    /**
     * @param obj1
     * @param obj2
     * @brief Guarda una relacion n a n entre dos objetos
     */
    template <class T3,class T4>
    void virtual saveRelacion(T3 obj1, T4 obj2);
    
    /**
     * @param obj
     * @param filtros
     * @brief Ejecuta una consulta en la base de datos con filtros como parametros en select
     */
    template <class T5>
    QVector<T5> virtual query(T5 obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();
};

#endif //_GESTORBASEDATOS_H
