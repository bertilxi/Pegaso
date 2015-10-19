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
     */
    T load(T obj, int id);
    
    /**
     * @param objs
     */
    void save(QVector<T> objs);
    
    /**
     * @param objs
     * @param id
     */
    void save(QVector<T> objs, int id);
    
    /**
     * @param obj1
     * @param obj2
     */
    void saveRelacion(T1 obj1, T2 obj2);
    
    /**
     * @param obj
     * @param filtros
     */
    QVector<T> query(T obj, QVector<QString> filtros);
    
    void beginTransaction();
    
    void commit();
};

#endif //_GESTORBASEDATOS_H