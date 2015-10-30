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
        return NULL;
    }
}

/**
 * @brief carga varias competencias inicializandolas parcialmente
 * @param dto dto con los filtros para buscar competencias
 * @return una lista de punteros a competencias
 *
 * Solo se carga el id y nombre de la competencia, su estado, el NOMBRE
 * de su modalidad y el ID de su deporte.
 */
QVector<Competencia *> GestorBaseDatos::getCompetenciasLazy(const DtoGetCompetencia *dto) const{

    /*
    SELECT C.id_competencia, C.nombre, D.id_deporte, M.nombre, C.estado
    FROM Competencia C, Deporte D, Tipo_modalidad M
    WHERE C.id_usuario = id_usuarioP
        C.id_modalidad = id_modalidadP AND C.id_modalidad = M.id_modalidad AND
        C.id_deporte = id_deporteP AND C.id_deporte = D.id_deporte AND
        C.estado = estadoP AND
        C.nombre LIKE '%nombreP%'
        */

    QString querystr;

    querystr += "SELECT C.id_competencia, C.nombre, D.id_deporte, M.nombre, C.estado ";
    querystr += "FROM Competencia C, Deporte D, Tipo_modalidad M WHERE ";

    bool primeraCondicion = true;
    if(dto->usuarioId != -1)
    {
        querystr += "C.id_usuario = " + QString::number(dto->usuarioId);
        primeraCondicion = false;
    }

    if(dto->tipoModalidadId != -1)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.id_modalidad = " + QString::number(dto->tipoModalidadId);
        primeraCondicion = false;
    }

    if(dto->deporte != NULL)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.id_deporte = " + QString::number(dto->deporte->getId());
        primeraCondicion = false;
    }

    if(!dto->estado.isNull())
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.estado = " + dto->estado;
        primeraCondicion = false;
    }

    if(!dto->nombreCompetencia.isNull())
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.nombre LIKE '%" + dto->nombreCompetencia + "%'";
        primeraCondicion = false;
    }

    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND C.id_deporte = D.id_deporte";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
    }

    QVector<Competencia *> competencias;

    while (query.next()) {

        Competencia *comp = new (std::nothrow) Competencia;
        if(comp == NULL){
            qDebug() << "No se pudo alocar memoria para Competencia";
            return QVector<Competencia *>();
        }
        comp->setId(query.value(0).toInt());
        comp->setNombre(query.value(1).toString());

        Deporte *deporte = new (std::nothrow) Deporte;
        if(deporte == NULL){
            qDebug() << "No se pudo alocar memoria para Deporte";
            ///Es necesario destruir la competencia
            return QVector<Competencia *>();
        }
        deporte->setId(query.value(2).toInt());
        comp->setDeporte(deporte);

        Modalidad *modalidad = new (std::nothrow) Modalidad;
        if(modalidad == NULL){
            qDebug() << "No se pudo alocar memoria para Modalidad";
            ///Es necesario destruir la competencia
            return QVector<Competencia *>();
        }
        modalidad->setNombre(query.value(3).toString());
        comp->setModalidad(modalidad);

        comp->setEstado(query.value(4).toString());

        competencias.push_back(comp);

    }

    return competencias;
}

//temporal
bool GestorBaseDatos::save(QVector<Participante *> participantes, int id_externo){
    Atributo id_externoA("id_competencia",QString::number(id_externo));
    return this->save(participantes, &id_externoA);
}


/**
 * @param objptrs es una lista de punteros a objetos
 * @param id es la fk
 * @brief Guarda una lista de objetos que necesitan una fk pero el objeto no la conoce
 * @return bool indica si la operacion fue exitosa
 */
template <class T1>
bool GestorBaseDatos::save(QVector<T1 *> objptrs, Atributo *id_externo /* = NULL */){

    QString tabla;
    QVector<Atributo> atributos;
    int ObjetoId;
    for(int i = 0; i < objptrs.size(); i++)
    {
        tabla = objptrs[i]->getTable();
        atributos = objptrs[i]->getAtributos();
        if(id_externo != NULL){
            atributos.push_back(*id_externo);
        }

        ObjetoId = this->armarQuery(tabla, atributos);
        if(ObjetoId != -1){
            objptrs[i]->setId(ObjetoId); //se agrega al objeto su id, asignado por la BD
        }
        else
        {
            return false;
        }
    }

    return true;
}




/**
 * @param obj1
 * @param obj2
 * @brief Guarda una relacion n a n entre dos objetos
 *
 * obj1.getTable(obj2) debe retornar la tabla de la relacion entre obj1 y obj2.
 * obj1.getCampos(obj2) debe retornar los atributos id correspondientes a la relacion
 * entre obj1 y obj2. En cada uno de ellos, campo debe estar seteado con el nombre
 * correspondiente y valor debe ser la cadena vacia.
 */
template <class T2,class T3>
bool GestorBaseDatos::saveRelacion(T2 *obj1, T3 *obj2){
    QString tabla = obj1->getTable(*obj2);
    QVector<Atributo> atributos = obj1->getAtributos(*obj2);
    atributos[0].valor = obj1->getId();
    atributos[1].valor = obj2->getId();

    QString querystr = "insert or replace into " + tabla + " ( " ;

    int j;
    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += atributos[j].campo + " , " ;
    }
    querystr += atributos[j].campo + ") values ( " ;

    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += "'" + atributos[j].valor + "'" + " , ";
    }
    querystr += "'" + atributos[j].valor + "' ) ";

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
template <class T4>
QVector<T4> GestorBaseDatos::query(T4 obj, QVector<QString> filtros) {
    return NULL;
}

void GestorBaseDatos::beginTransaction() {

}

void GestorBaseDatos::commit() {

}


/**
 * @brief utiliza el nombre de una tabla y conjuntos columna-valor (atributos)
 * para armar un insert SQL y ejecutarlo en la BD.
 * @param tabla
 * @param atributos
 * @return id del objeto que se acaba de guardar, asignado por la BD
 */
int armarQuery(QString tabla, const QVector<Atributo> &atributos){

    QString querystr;

    querystr = "insert or replace into " + tabla + " ( " ;

    int j;
    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += atributos[j].campo + " , " ;
    }
    querystr += atributos[j].campo + ") values ( " ;

    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += "'" + atributos[j].valor + "'" + " , ";
    }
    querystr += "'" + atributos[j].valor + "' ) ";

    QSqlQuery query;

    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return -1;
    }

    return query.lastInsertId().toInt();
}
