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
template <class T>
T GestorBaseDatos::load(T obj, int id) {
	// le pedimos al objeto sus datos para poder buscarlo en la base de datos
	QString tabla = getTable(obj);
	QString atributo = obj.getAtributo();
	QString valor = obj.getValor();
	QString querystr="select * from " + tabla + " where " + atributo + " = " + valor + "'";

    QSqlQuery query;
    if(query.exec(querystr)){

        QSqlRecord record = query.record();

        //setters

        obj.setAll(record);
        qDebug() << "Consulta exitosa";
        return obj;

    }
    else {
        qDebug() << "La consulta ha fallado";
        return null;
    }
}

/**
 * @param objs
 */
template <class T1>
void GestorBaseDatos::save(QVector<T1> objs) {

}

/**
 * @param objs
 * @param id
 */
template <class T2> 
void GestorBaseDatos::save(QVector<T2> objs, int id) {

}

/**
 * @param obj1
 * @param obj2
 */
template <class T3,class T4>
void GestorBaseDatos::saveRelacion(T3 obj1, T4 obj2) {

}

/**
 * @param obj
 * @param filtros
 * @return QVector<T>
 */
template <class T5>
QVector<T5> GestorBaseDatos::query(T5 obj, QVector<QString> filtros) {
    return null;
}

void GestorBaseDatos::beginTransaction() {

}

void GestorBaseDatos::commit() {

}