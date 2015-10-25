/**
 * Project Pegaso
 */

#include <QSqlQuery>
#include <QDebug>

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
        return NULL;
    }
}

/**
 * @param objptrs es una lista de punteros a objetos
 * @return bool indica si la operacion fue exitosa
 */
template <class T1>
bool GestorBaseDatos::save(QVector<T1 *> objptrs) {

    QString tabla = objptrs[0]->getTable();
    QVector<QString> campos = objptrs[0]->getCampos(); //incluido el id si ya estaba persistido (sino, no).
    QVector<QString> valores = objptrs[0]->getValores();

    QString querystr;

    int i;
    for(i = 0; i < objptrs.size(); i++)
    {
        querystr = "insert or replace into " + tabla + " ( " ;

        int j;
        for (j = 0; j < campos.size()-1; ++j)
        {
            querystr += campos[j] + " , " ;
        }
        querystr += campos[j] + ") values ( " ;

        for (j = 0; j < valores.size()-1; ++j)
        {
            querystr += "'" + valores[j] + "'" + " , ";
        }
        querystr += "'" + valores[j] + "' ) ";

        QSqlQuery query;

        // consulta
        if(!query.exec(querystr)){
            qDebug() << "La consulta " << i << " ha fallado";
            return false;
        }
        else{
            qDebug() << "Consulta " << i << " exitosa";
        }

        objptrs[i]->id = query.lastInsertId(); //se agrega a cada objeto su id, asignado por la BD
    }

    return true;
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
    return NULL;
}

void GestorBaseDatos::beginTransaction() {

}

void GestorBaseDatos::commit() {

}
