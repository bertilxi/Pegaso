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
    template <class T>
    T virtual load(T obj, int id);
    
    /**
     * @param objs
     */
    template <class T1>
    void virtual save(QVector<T1> objs);
    
    /**
     * @param objs
     * @param id
     */
    template <class T2>
    void virtual save(QVector<T2> objs, int id);
    
    /**
     * @param obj1
     * @param obj2
     */
    template <class T3,class T4>
    void virtual saveRelacion(T3 obj1, T4 obj2);
    
    /**
     * @param obj
     * @param filtros
     */
    template <class T5>
    QVector<T5> virtual query(T5 obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();
};

#endif //_GESTORBASEDATOS_H
