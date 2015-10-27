/**
 * Project Pegaso
 */

#include <QSqlQuery>
#include <QDebug>

#include "GestorBaseDatos.h"
#include "../Grupo Competencia/Competencia.h"

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

    return this->armarYEjecutar(objptrs, tabla, campos, valores);
}





/*
bool GestorBaseDatos::saveCompetencia(Competencia* comp, int usuarioId){
    implementado en "GestorBaseDatosSaveEspeciales.h"
}
*/




/**
 * @param objptrs es una lista de punteros a objetos
 * @param id es la fk
 * @brief Guarda una lista de objetos que necesitan una fk pero el objeto no la conoce
 * @return bool indica si la operacion fue exitosa
 *
 * objs.getCampos() retorna una lista que debe incluir como ULTIMO elemento el campo
 * al que corresponde el parametro id.
 */
template <class T2> 
bool GestorBaseDatos::save(QVector<T2 *> objptrs, int id) {

    QString tabla = objptrs[0]->getTable();
    QVector<QString> campos = objptrs[0]->getCampos(); //incluido el id si ya estaba persistido (sino, no).
    QVector<QString> valores = objptrs[0]->getValores();
    valores.push_back(QString::number(id));

    return this->armarYEjecutar(objptrs, tabla, campos, valores);
}



/**
 * @brief arma y ejecuta queries para guardar una lista de objetos
 * @param objptrs punteros a objetos
 * @param tabla nombre de la tabla de la BD donde guardar los objetos
 * @param campos nombre de los campos donde guardar los datos
 * @param valores valores de los datos a guardar
 * @return true si tuvo exito, false si fallo
 */
template <class Ta>
bool GestorBaseDatos::armarYEjecutar(QVector<Ta *> &objptrs, QString &tabla, QVector<QString> &campos, QVector<QString> &valores){

    QString querystr;

    for(int i = 0; i < objptrs.size(); i++)
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
            qDebug() << "La consulta que dio error fue: " << querystr;
            return false;
        }
        else{
            qDebug() << "Consulta " << i << " exitosa";
        }

        objptrs[i]->id = query.lastInsertId().toInt(); //se agrega a cada objeto su id, asignado por la BD
    }

    return true;
}


/**
 * @param obj1
 * @param obj2
 * @brief Guarda una relacion n a n entre dos objetos
 *
 * obj1.getTable(obj2) debe retornar la tabla de la relacion entre obj1 y obj2.
 * obj1.getCampos(obj2) debe retornar primero el nombre del campo id de obj1, y
 * segundo el nombre del campo id de obj2.
 */
template <class T3,class T4>
bool GestorBaseDatos::saveRelacion(T3 *obj1, T4 *obj2){
    QString tabla = obj1->getTable(obj2);
    QVector<QString> campos = obj1->getCampos(obj2);
    QVector<QString> valores;
    valores.push_back(obj1->getId);
    valores.push_back(obj2->getId);

    QString querystr = "insert or replace into " + tabla + " ( " ;

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

    // consulta(
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return false;
    }
    else{
        qDebug() << "Consulta exitosa";
    }

    return true;
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
