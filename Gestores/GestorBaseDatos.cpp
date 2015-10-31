/**
 * Project Pegaso
 */


#include "GestorBaseDatos.h"
#include <algorithm>

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
SELECT C.id_competencia, C.nombre, D.id_deporte, TM.nombre, C.estado
FROM Competencia C, Deporte D, Modalidad M, Tipo_modalidad TM
WHERE C.id_usuario = id_usuarioP
    C.id_modalidad = id_modalidadP AND C.id_modalidad = M.id_modalidad AND
    M.id_tipo_modalidad = TM.id_tipo_modalidad AND
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

    if(dto->deporteId != -1)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.id_deporte = " + QString::number(dto->deporteId);
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
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
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

Competencia *GestorBaseDatos::getCompetenciaFull(int id_comp) const{

    //CARGA COMPETENCIA, MODALIDAD Y DEPORTE

/*
SELECT C.nombre, C.estado, C.fecha_y_horaB, C.borrado, C.reglamento,
D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse,
M.pto_empate, M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre,
TR.id_tipo_resultado, TR.nombre
FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D
WHERE C.id_competencia = id_comp AND
    C.id_modalidad = M.id_modalidad AND
    M.id_tipo_modalidad = TM.id_tipo_modalidad AND
    C.id_tipo_resultado = TR.id_tipo_resultado AND
    C.id_deporte = D.id_deporte
*/


    QString querystr;
    querystr += "SELECT C.nombre, C.estado, C.fecha_y_horaB, C.borrado, C.reglamento";
    querystr += ", D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse";
    querystr += ", M.pto_empate, M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre";
    querystr += ", TR.id_tipo_resultado, TR.nombre";
    querystr += " FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D";
    querystr += " WHERE C.id_competencia = " + QString::number(id_comp);
    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND C.id_tipo_resultado = TR.id_tipo_resultado";
    querystr += " AND C.id_deporte = D.id_deporte";

    QSqlQuery query;

    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return NULL;
    }

    if(!query.next()){
        qDebug() << "Error Base de datos: No hay ninguna competencia con ese id";
        return NULL;
    }

    Competencia *comp = new Competencia;

    comp->setNombre(query.value(0).toString());
    comp->setEstado(query.value(1).toString());
    comp->setFecha_y_horaB(query.value(2).toString());
    comp->setBorrado((bool)query.value(3).toInt());
    comp->setReglamento(query.value(4).toString());

    Deporte *dep = new Deporte;
    dep->setId(query.value(5).toInt());
    dep->setNombre(query.value(6).toString());

    comp->setDeporte(dep);

    Modalidad *mod = new Modalidad;
    mod->setId(query.value(7).toInt());
    mod->setPuntos_ganar(query.value(8).toInt());
    mod->setPuntos_presentarse(query.value(9).toInt());
    mod->setPuntos_empate(query.value(10).toInt());
    mod->setCant_max_sets(query.value(11).toInt());
    mod->setId_nombre(query.value(12).toInt());
    mod->setNombre(query.value(13).toString());
    mod->setId_tipo_resultado(query.value(14).toInt());
    mod->setTipo_resultado(query.value(15).toString());

    comp->setModalidad(mod);

///______________________________________________________________________________________________________________________
    //CARGA DISPONIBILIDADES

    /*
    SELECT SA.disponibilidad, SA.id_lugar
    FROM Se_asignan SA
    WHERE SA.id_competencia = id_comp
            */

    querystr.clear();

    querystr += "SELECT SA.disponibilidad, SA.id_lugar";
    querystr += " FROM Se_asignan SA WHERE SA.id_competencia = " + QString::number(id_comp);

    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return NULL;
    }

    QVector<Disponibilidad *> disps;

    while(query.next()){
        Disponibilidad *disp = new Disponibilidad;

        disp->setDisponibilidad(query.value(0).toInt());

        Lugar *lugar = new Lugar;

        //solo seteo el id de lugar. debera usarse ese id para reemplazar este lugar
        //temporal por el real objeto lugar.
        lugar->setId(query.value(1).toInt());

        disp->setLugar(lugar);

        disps.push_back(disp);
    }

    comp->setDisponibilidades(disps);

///______________________________________________________________________________________________________________________
    //CARGA PARTICIPANTES

/*
SELECT id_participante, imagen, nombre, correo, puntos, pg, pp, pe, tf,
tc, dif
FROM Participante
WHERE id_competencia = id_comp*/

    querystr.clear();

    querystr += "SELECT id_participante, imagen, nombre, correo, puntos, pg, pp, pe, tf, tc, dif";
    querystr += " FROM Participante WHERE id_competencia = " + QString::number(id_comp);
    querystr += " ORDER BY id_participante ASC";

    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return NULL;
    }

    QVector<Participante *> partics;

    while(query.next()){
        Participante *partic = new Participante;
        partic->setId(query.value(0).toInt());
        partic->setImg(query.value(1).toString());
        partic->setNombre(query.value(2).toString());
        partic->setCorreo(query.value(3).toString());

        Puntaje *pun = new Puntaje;
        pun->setPuntos(query.value(4).toInt());
        pun->setPG(query.value(5).toInt());
        pun->setPP(query.value(6).toInt());
        pun->setPE(query.value(7).toInt());
        pun->setTF(query.value(8).toInt());
        pun->setTC(query.value(9).toInt());
        pun->setDif(query.value(10).toInt());

        partic->setPuntaje(pun);

        partics.push_back(partic);
    }

///______________________________________________________________________________________________________________________
    //CARGA HISTORIALES DE MODIFICACION DE PARTICIPANTES

/*
SELECT id_modificacion, nombre, correo, imagen
FROM Historial_participante
WHERE id_participante = id_part
*/

    //para cada participante, cargo sus historiales de modificacion
    for(int i = 0; i < partics.size(); i++){
        querystr.clear();

        querystr += "SELECT id_modificacion, nombre, correo, imagen";
        querystr += " FROM Historial_participante WHERE id_participante = ";
        querystr += QString::number( partics[i]->getId() );

        // consulta
        if(!query.exec(querystr)){
            qDebug() << "La consulta ha fallado";
            qDebug() << "La consulta que dio error fue: " << querystr;
            return NULL;
        }

        QVector<HistorialParticipante *> hists;

        while(query.next()){
            HistorialParticipante *hist = new HistorialParticipante;
            hist->setId(query.value(0).toInt());
            hist->setNombre(query.value(1).toString());
            hist->setCorreo(query.value(2).toString());
            hist->setImagen(query.value(3).toString());

            hists.push_back(hist);
        }

        partics[i]->setHistorial(hists);
    }

    comp->setParticipantes(partics);

///______________________________________________________________________________________________________________________
    //CARGA PARTIDOS

/*
SELECT id_partido, fecha, ronda, id_lugar, equipoA, equipoB
FROM Partido
WHERE id_competencia = id_comp
*/

    querystr.clear();

    querystr += "SELECT id_partido, fecha, ronda, id_lugar, equipoA, equipoB";
    querystr += " FROM Partido WHERE id_competencia = " + QString::number(id_comp);

    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        return NULL;
    }

    QVector<Partido *> partidos;
    int equipoA, equipoB;

    while(query.next()){
        Partido *partido = new Partido;
        partido->setId(query.value(0).toInt());
        partido->setFecha(query.value(1).toInt());
        partido->setRonda(query.value(2).toString());

        Lugar *lugar = new Lugar;

        //solo seteo el id de lugar. debera usarse ese id para reemplazar este lugar
        //temporal por el real objeto lugar.
        lugar->setId(query.value(3).toInt());
        partido->setLugar(lugar);

        equipoA = query.value(3).toInt();
        equipoB = query.value(4).toInt();

        //Busco el equipoA entre los participantes de la Compentencia y lo relaciono al partido
        Participante particAux;
        Participante *particAuxPtr = &particAux;
        QVector<Participante *>::iterator index;

        particAuxPtr->setId(equipoA);
        index = std::lower_bound(partics.begin(),partics.end(),particAuxPtr,Participante::LessThan);
        partido->setEquipoA(*index);

        //Busco el equipoB entre los participantes de la Compentencia y lo relaciono al partido
        particAuxPtr->setId(equipoB);
        index = std::lower_bound(partics.begin(),partics.end(),particAuxPtr,Participante::LessThan);
        partido->setEquipoB(*index);
    }

///______________________________________________________________________________________________________________________
    //CARGA RESULTADOS

    for(int i = 0; i < partidos.size(); i++){

        //si el resultado es de tipo Resultado
        if(comp->getModalidad()->getTipo_resultado() == "Resultado")
        {
            querystr = this->generarQueryResultado( QString::number(partidos[i]->getId()) );

            // consulta
            if(!query.exec(querystr)){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                return NULL;
            }

            QVector<Resultado *> resultadosModificados;
            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 resultadoA
                 * 2 resultadoB
                 * 3 partido_actual
                 * */

                Resultado *resultado = new Resultado;
                resultado->setId(query.value(0).toInt());
                resultado->setResultadoA(query.value(1).toString());
                resultado->setResultadoB(query.value(2).toString());

                //si no es el resultado actual, lo pongo en una lista de modificados
                if(query.value(3).isNull()){
                    resultadosModificados.push_back(resultado);
                }

                //si es es resultado actual, seteo el partido con él
                else
                {
                    partidos[i]->setActual(resultado);
                }
            }

            //al final, seteo el partido con su lista de resultados modificados
            partidos[i]->setModificado(resultadosModificados);


        }
        //si el resultado es de tipo Puntos
        else if(comp->getModalidad()->getTipo_resultado() == "Puntos")
        {
            querystr = this->generarQueryPuntos( QString::number(partidos[i]->getId()) );

            // consulta
            if(!query.exec(querystr)){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                return NULL;
            }

            QVector<Resultado *> resultadosModificados;
            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 resultadoA
                 * 2 resultadoB
                 * 3 partido_actual
                 * 4 puntosA
                 * 5 puntosB
                 * */

                Puntos *puntos = new Puntos;
                puntos->setId(query.value(0).toInt());
                puntos->setResultadoA(query.value(1).toString());
                puntos->setResultadoB(query.value(2).toString());
                puntos->setPuntosA(query.value(4).toInt());
                puntos->setPuntosB(query.value(5).toInt());

                //si no es el resultado actual, lo pongo en una lista de modificados
                if(query.value(3).isNull()){
                    resultadosModificados.push_back(puntos);
                }

                //si es es resultado actual, seteo el partido con él
                else
                {
                    partidos[i]->setActual(puntos);
                }
            }

            //al final, seteo el partido con su lista de resultados modificados
            partidos[i]->setModificado(resultadosModificados);


        }
        //si el resultado es de tipo Sets:
        else if(comp->getModalidad()->getTipo_resultado() == "Sets")
        {
            querystr = generarQuerySets( QString::number(partidos[i]->getId()) );

            // consulta
            if(!query.exec(querystr)){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                return NULL;
            }

            QVector<Set *> grupoSet;
            QVector<Resultado *> resultadosModificados;
            bool primerResultado = true;
            int resultadoActual = -1000;

            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 resultadoA
                 * 2 resultadoB
                 * 3 partido_actual
                 * 4 nro_set
                 * 5 puntosA
                 * 6 puntosB
                 * */

                //si el set que leemos pertenece a un nuevo Resultado
                if(resultadoActual != query.value(0).toInt()){
                    resultadoActual = query.value(0).toInt();

                    //si ya hemos cargado los todos los sets correspondientes a un Resultado
                    if(primerResultado == false){

                        //creo un resultado de tipo "Sets"
                        Sets *sets = new Sets;

                        //lo seteo con los atributos de cualquier Resultado
                        sets->setId(query.value(0).toInt());
                        sets->setResultadoA(query.value(1).toString());
                        sets->setResultadoB(query.value(2).toString());

                        //lo seteo con sus correspondientes "Set"
                        sets->setSets(grupoSet);

                        //si no es el resultado actual, lo pongo en una lista de modificados
                        if(query.value(3).isNull()){
                            resultadosModificados.push_back(sets);
                        }

                        //si es es resultado actual, seteo el partido con él
                        else
                        {
                            partidos[i]->setActual(sets);
                        }
                    }

                    primerResultado = false;
                }

                Set *set = new Set;
                set->setNro_set(query.value(4).toInt());
                set->setPuntosA(query.value(5).toInt());
                set->setPuntosB(query.value(6).toInt());

                grupoSet.push_back(set);

                //fin while()
            }

            //repito por ultima vez el codigo para guardar el ultimo Resultado

            //creo un resultado de tipo "Sets"
            Sets *sets = new Sets;

            //lo seteo con los atributos de cualquier Resultado
            sets->setId(query.value(0).toInt());
            sets->setResultadoA(query.value(1).toString());
            sets->setResultadoB(query.value(2).toString());

            //lo seteo con sus correspondientes "Set"
            sets->setSets(grupoSet);

            //si no es el resultado actual, lo pongo en una lista de modificados
            if(query.value(3).isNull()){
                resultadosModificados.push_back(sets);
            }

            //si es es resultado actual, seteo el partido con él
            else
            {
                partidos[i]->setActual(sets);
            }


            //al final, seteo el partido con su lista de resultados modificados
            partidos[i]->setModificado(resultadosModificados);
        }
        else
        {
            qDebug() << "El tipo de resultado no coincide con 'Resultado', 'Puntos' o 'Sets'";
        }


        //fin for("para cada partido")
    }


    //seteo competencia con sus partidos y resultados
    comp->setPartidos(partidos);


    return comp;
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

        ObjetoId = this->armarQuerySave(tabla, atributos);
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
int armarQuerySave(QString tabla, const QVector<Atributo> &atributos){

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


QString GestorBaseDatos::generarQueryResultado(QString partidoId) const{
    /**
    SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual
    FROM Resultado R
    WHERE R.partido_actual = id_partido OR
        R.partido_modificado = id_partido*/

    QString querystr;
    querystr += "SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual";
    querystr += " FROM Resultado";
    querystr += " WHERE R.partido_actual = " + partidoId;
    querystr += " OR R.partido_modificado = " + partidoId;

    return querystr;
}


QString GestorBaseDatos::generarQueryPuntos(QString partidoId) const{
    /**
    SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual,
        P.puntosA, P.puntosB,
    FROM Resultado R JOIN Puntos P USING(id_resultado)
    WHERE R.partido_actual = id_partido OR
        R.partido_modificado = id_partido*/

    QString querystr;
    querystr += "SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual";
    querystr += ", P.puntosA, P.puntosB";
    querystr += " FROM Resultado R JOIN Puntos P USING(id_resultado)";
    querystr += " WHERE R.partido_actual = " + partidoId;
    querystr += " OR R.partido_modificado = " + partidoId;

    return querystr;
}


QString GestorBaseDatos::generarQuerySets(QString partidoId) const{
    /**
    SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual,
        S.nro_set, S.puntosA, S.puntosB
    FROM Resultado R JOIN Sets S USING(id_resultado)
    WHERE R.partido_actual = id_partido OR
        R.partido_modificado = id_partido
    ORDER BY R.id_resultado, S.nro_set ASC*/

    QString querystr;
    querystr += "SELECT R.id_resultado, R.resultadoA, R.resultadoB, R.partido_actual";
    querystr += ", S.nro_set, S.puntosA, S.puntosB";
    querystr += " FROM Resultado R JOIN Sets S USING(id_resultado)";
    querystr += " WHERE R.partido_actual = " + partidoId;
    querystr += " OR R.partido_modificado = " + partidoId;
    querystr += " ORDER BY R.id_resultado, S.nro_set ASC";

    return querystr;
}
