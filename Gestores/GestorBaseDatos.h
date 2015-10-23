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
    T virtual load(T obj, int id);
    
    /**
     * @param objs
     */
    void virtual save(QVector<T> objs);
    
    /**
     * @param objs
     * @param id
     */
    void virtual save(QVector<T> objs, int id);
    
    /**
     * @param obj1
     * @param obj2
     */
    void virtual saveRelacion(T1 obj1, T2 obj2);
    
    /**
     * @param obj
     * @param filtros
     */
    QVector<T> virtual query(T obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();
};

#endif //_GESTORBASEDATOS_H
