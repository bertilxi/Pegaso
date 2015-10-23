/**
 * Project Pegaso
 */


#include "GestorBaseDatos.h"

/**
 * GestorBaseDatos implementation
 */


/**
 * @param obj
 * @param id
 * @return T
 */
T GestorBaseDatos::load(T obj, int id) {
    return null;
}

/**
 * @param objs
 */
void GestorBaseDatos::save(QVector<T> objs) {

}

/**
 * @param objs
 * @param id
 */
void GestorBaseDatos::save(QVector<T> objs, int id) {

}

/**
 * @param obj1
 * @param obj2
 */
void GestorBaseDatos::saveRelacion(T1 obj1, T2 obj2) {

}

/**
 * @param obj
 * @param filtros
 * @return QVector<T>
 */
QVector<T> GestorBaseDatos::query(T obj, QVector<QString> filtros) {
    return null;
}

void GestorBaseDatos::beginTransaction() {

}

void GestorBaseDatos::commit() {

}