///**
// * Project Pegaso
// */

//#include <QSqlQuery>
//#include <QDebug>

//#include "GestorBaseDatos.h"
//#include "../Grupo Competencia/Competencia.h"

///**
// * GestorBaseDatos implementation
// */


///**
// * @param obj
// * @param id
// * @return T
// */
//template <class T>
//T GestorBaseDatos::load(T obj, int id) {
//	// le pedimos al objeto sus datos para poder buscarlo en la base de datos
//	QString tabla = getTable(obj);
//	QString atributo = obj.getAtributo();
//	QString valor = obj.getValor();
//	QString querystr="select * from " + tabla + " where " + atributo + " = " + valor + "'";

//    QSqlQuery query;
//    if(query.exec(querystr)){

//        QSqlRecord record = query.record();

//        //setters

//        obj.setAll(record);
//        qDebug() << "Consulta exitosa";
//        return obj;

//    }
//    else {
//        qDebug() << "La consulta ha fallado";
//        return NULL;
//    }
//}




///**
// * @param objptrs es una lista de punteros a objetos
// * @param id es la fk
// * @brief Guarda una lista de objetos que necesitan una fk pero el objeto no la conoce
// * @return bool indica si la operacion fue exitosa
// */
//template <class T1>
//bool GestorBaseDatos::save(QVector<T1 *> objptrs, Atributo *id_externo /* = NULL */){

//    QString tabla;
//    QVector<Atributo> atributos;
//    int ObjetoId;
////    for(int i = 0; i < objptrs.size(); i++)
////    {
////        tabla = objptrs[i]->getTable();
////        atributos = objptrs[i]->getAtributos();
////        if(id_externo != NULL){
////            atributos.push_back(*id_externo);
////        }

////        ObjetoId = this->armarQuery(tabla, atributos);
////        if(ObjetoId != -1){
////            objptrs[i]->setId(ObjetoId); //se agrega al objeto su id, asignado por la BD
////        }
////        else
////        {
////            return false;
////        }
////    }

//    return true;
//}




///**
// * @param obj1
// * @param obj2
// * @brief Guarda una relacion n a n entre dos objetos
// *
// * obj1.getTable(obj2) debe retornar la tabla de la relacion entre obj1 y obj2.
// * obj1.getCampos(obj2) debe retornar los atributos id correspondientes a la relacion
// * entre obj1 y obj2. En cada uno de ellos, campo debe estar seteado con el nombre
// * correspondiente y valor debe ser la cadena vacia.
// */
//template <class T2,class T3>
//bool GestorBaseDatos::saveRelacion(T2 *obj1, T3 *obj2){
////    QString tabla = obj1->getTable(*obj2);
////    QVector<Atributo> atributos = obj1->getAtributos(*obj2);
////    atributos[0].valor = obj1->getId();
////    atributos[1].valor = obj2->getId();

////    QString querystr = "insert or replace into " + tabla + " ( " ;

////    int j;
////    for (j = 0; j < atributos.size()-1; ++j)
////    {
////        querystr += atributos[j].campo + " , " ;
////    }
////    querystr += atributos[j].campo + ") values ( " ;

////    for (j = 0; j < atributos.size()-1; ++j)
////    {
////        querystr += "'" + atributos[j].valor + "'" + " , ";
////    }
////    querystr += "'" + atributos[j].valor + "' ) ";

////    QSqlQuery query;

////    // consulta(
////    if(!query.exec(querystr)){
////        qDebug() << "La consulta ha fallado";
////        qDebug() << "La consulta que dio error fue: " << querystr;
////        return false;
////    }
////    else{
////        qDebug() << "Consulta exitosa";
////    }

//    return true;
//}

///**
// * @param obj
// * @param filtros
// * @return QVector<T>
// */
//template <class T4>
//QVector<T4> GestorBaseDatos::query(T4 obj, QVector<QString> filtros) {
//    return NULL;
//}

//void GestorBaseDatos::beginTransaction() {

//}

//void GestorBaseDatos::commit() {

//}


///**
// * @brief utiliza el nombre de una tabla y conjuntos columna-valor (atributos)
// * para armar un insert SQL y ejecutarlo en la BD.
// * @param tabla
// * @param atributos
// * @return id del objeto que se acaba de guardar, asignado por la BD
// */
//int armarQuery(QString tabla, const QVector<Atributo> &atributos){

//    QString querystr;

//    querystr = "insert or replace into " + tabla + " ( " ;

//    int j;
//    for (j = 0; j < atributos.size()-1; ++j)
//    {
//        querystr += atributos[j].campo + " , " ;
//    }
//    querystr += atributos[j].campo + ") values ( " ;

//    for (j = 0; j < atributos.size()-1; ++j)
//    {
//        querystr += "'" + atributos[j].valor + "'" + " , ";
//    }
//    querystr += "'" + atributos[j].valor + "' ) ";

//    QSqlQuery query;

//    // consulta
//    if(!query.exec(querystr)){
//        qDebug() << "La consulta ha fallado";
//        qDebug() << "La consulta que dio error fue: " << querystr;
//        return -1;
//    }

//    return query.lastInsertId().toInt();
//}


//bool GestorBaseDatos::saveCompetencia(Competencia *comp, Atributo usuarioId){

//    bool status = true;

//    //guardo modalidad
////    Modalidad *mod = comp->getModalidad();
////    status &= this->save(QVector<Modalidad *>(1,mod));

////    //guardo los atributos simples de competencia
////    status &= this->save(QVector<Competencia *>(1,comp), &usuarioId);

////    //guardo las disponibilidades
////    QVector<Disponibilidad *> disps = comp->getDisponibilidades();
////    Atributo competenciaId("id_competencia",QString::number(comp->getId()));
////    status &= this->save(disps, &competenciaId);

////    //guardo los participantes
////    QVector<Participante *> participantes = comp->getParticipantes();
////    status &= this->save(participantes, &competenciaId);

////    //guardo los historiales de cada participante
////    for(int i = 0; i < participantes.size(); i++){
////        Atributo participanteId("id_participante",QString::number(participantes[i]->getId()));
////        status &= this->save(participantes[i]->getHistorial(), &participanteId);
////    }

////    //guardo los partidos
////    QVector<Partido *> partidos = comp->getPartidos();
////    status &= this->save(partidos, &competenciaId);

////    for(int i = 0; i < partidos.size(); i++){

////        //guardo los resultados de cada partido
////        status &= this->saveResultado(partidos[i]->getActual(), Atributo("partido_actual",QString::number(partidos[i]->getId())));

////        //guardo el historial de cada partido
////        QVector<Resultado *> modificados = partidos[i]->getModificado();
////        for(int j = 0; j < modificados.size(); j++){
////            status &= this->saveResultado(modificados[j], Atributo("partido_modificado",QString::number(partidos[i]->getId())));
////        }
////    }

////    for(int i = 0; i < partidos.size(); i++){
////        QVector<Partido *> sucesores = partidos[i]->getSucesores();
////        for(int j = 0; j < sucesores.size(); j++){
////            status &= this->saveRelacion(partidos[i],sucesores[j]);
////        }
////    }
////    return status;
//}

//bool GestorBaseDatos::saveResultado(Resultado *resultado, Atributo partidoId){
//    bool status = true;

////    Puntos *puntos = dynamic_cast<Puntos *>(resultado);
////    if(puntos != NULL)  //si es de clase Puntos
////    {
////        status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
////        Atributo resultadoId("id_resultado",QString::number(resultado->getId()));
////        status &= this->save(QVector<Puntos *>(1,puntos), &resultadoId);
////    }
////    else
////    {
////        Sets *sets = dynamic_cast<Sets *>(resultado);
////        if(sets != NULL)    //si es de clase Sets
////        {
////            status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
////            Atributo resultadoId("id_resultado",QString::number(resultado->getId()));
////            status &= this->save(sets->getSets(), &resultadoId);
////        }
////        else    //si es de clase Resultado
////        {
////            status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
////        }
////    }
////-----------------------------------------------------------------------------------------------

//    ///Problema: getTable() no es virtual. Siempre devolverá "Resultado".
///*
//    switch(tabla[0].toLatin1()){
//    case 'R': //"Resultado"
//        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
//        break;
//    case 'P': //"Puntos"
//        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
//        status &= this->save(QVector<Puntos *>(1,dynamic_cast<Puntos *>(resultado)), Atributo("id_resultado",resultado->getId()));
//        break;
//    case 'S': //"Sets"
//        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
//        QVector<Sets *> sets = dynamic_cast<Sets *>(resultado)->getSets();
//        status &= this->save(sets, Atributo("id_resultado",resultado->getId()));
//        break;
//    }*/
//    return status;
//}
