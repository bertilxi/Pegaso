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

//        comp->setEstado(query.value(4).toString());

        competencias.push_back(comp);

    }

    return competencias;
}

Competencia *GestorBaseDatos::getCompetenciaFull(int id_comp) const{

    //CARGA COMPETENCIA, MODALIDAD Y DEPORTE

/*
SELECT C.nombre, TE.id_estado, TE.nombre, C.fecha_y_horaB, C.borrado, C.reglamento,
D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse,
M.pto_empate, M.empate ,M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre,
TR.id_tipo_resultado, TR.nombre
FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D, Tipo_estado TE
WHERE C.id_competencia = id_comp AND
    C.id_modalidad = M.id_modalidad AND
    M.id_tipo_modalidad = TM.id_tipo_modalidad AND
    C.id_tipo_resultado = TR.id_tipo_resultado AND
    C.id_deporte = D.id_deporte AND
    TE.id_estado = C.id_estado
*/


    QString querystr;
    querystr += "SELECT C.nombre, TE.id_estado, TE.nombre, C.fecha_y_horaB, C.borrado, C.reglamento";
    querystr += ", D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse";
    querystr += ", M.pto_empate, M.empate, M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre";
    querystr += ", TR.id_tipo_resultado, TR.nombre";
    querystr += " FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D, Tipo_estado TE";
    querystr += " WHERE C.id_competencia = " + QString::number(id_comp);
    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND M.id_tipo_resultado = TR.id_tipo_resultado";
    querystr += " AND C.id_deporte = D.id_deporte";
    querystr += " AND TE.id_estado = C.id_estado";

    QSqlQuery query;



    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        if (query.next())
        {
        } else {
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }
        return NULL;
    }


    if(!query.next()){
        qDebug() << "Error Base de datos: No hay ninguna competencia con ese id";
        return NULL;
    }

    Competencia *comp = new Competencia;

    Estado* est = new Estado();

    comp->setId(id_comp);
    comp->setNombre(query.value(0).toString());
//    est->getId(query.value(1).toInt());
//    est->getNombre(query.value(2).toString());

    comp->setEstado(est);

    comp->setFecha_y_horaB(query.value(3).toString());
    comp->setBorrado((bool)query.value(4).toInt());
    comp->setReglamento(query.value(5).toString());

    Deporte *dep = new Deporte;
    dep->setId(query.value(6).toInt());
    dep->setNombre(query.value(7).toString());

    comp->setDeporte(dep);

    Modalidad *mod = new Modalidad;

    mod->setId(query.value(8).toInt());
    mod->setPuntos_ganar(query.value(9).toInt());
    mod->setPuntos_presentarse(query.value(10).toInt());
    mod->setPuntos_empate(query.value(11).toInt());
    mod->setEmpate((bool)query.value(12).toInt());
    mod->setCant_max_sets(query.value(13).toInt());

    TipoModalidad* tipoMod = new TipoModalidad();

    tipoMod->setId(query.value(14).toInt());
    tipoMod->setNombre(query.value(15).toString());

//    mod->setTipoMod(tipoMod);

    TipoResultado* tipoRes = new TipoResultado();

    tipoRes->setId(query.value(16).toInt());
    tipoRes->setNombre(query.value(17).toString());

    mod->setTipoRes(tipoRes);

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

        equipoA = query.value(4).toInt();
        equipoB = query.value(5).toInt();

        //Busco el equipoA entre los participantes de la Compentencia y lo relaciono al partido
        Participante particAux;
        Participante *particAuxPtr = &particAux;
        QVector<Participante *>::iterator index;

        particAuxPtr->setId(equipoA);

        index = lower_bound(partics.begin(),partics.end(),particAuxPtr, Participante::LessThan);

        partido->setEquipoA(*index);

        //Busco el equipoB entre los participantes de la Compentencia y lo relaciono al partido
        particAuxPtr->setId(equipoB);
        index = lower_bound(partics.begin(),partics.end(),particAuxPtr,Participante::LessThan);
        partido->setEquipoB(*index);

        partidos.push_back(partido);
    }

///______________________________________________________________________________________________________________________
    //CARGA RESULTADOS

    for(int i = 0; i < partidos.size(); i++){

        //si el resultado es de tipo Resultado
        if(comp->getModalidad()->getTipoRes()->getNombre() == "Resultado")

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

                Res* resA = new Res();
                Res* resB = new Res();

                resA->setId(query.value(1).toInt());
                resA->setNombre(query.value(2).toString());
                resB->setId(query.value(3).toInt());
                resB->setNombre(query.value(4).toString());

                resultado->setResultadoA(resA);
                resultado->setResultadoB(resB);

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
        else if(comp->getModalidad()->getTipoRes()->getNombre() == "Puntos")
        {
            querystr = this->generarQueryPuntos( QString::number(partidos[i]->getId()) );

            // consulta
            if(!query.exec(querystr)){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                return NULL;
            }
            qDebug() << "Consulta: " << querystr;


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

                Res* resA = new Res();
                Res* resB = new Res();
                resA->setId(query.value(1).toInt());
                resA->setNombre(query.value(2).toString());
//                resB->setId(query.value(3).toString());
                resB->setNombre(query.value(4).toString());

                puntos->setResultadoA(resA);
                puntos->setResultadoB(resB);

                puntos->setPuntosA(query.value(6).toInt());
                puntos->setPuntosB(query.value(7).toInt());
                qDebug() << "Puntos A: " << query.value(6).toInt();
                qDebug() << "getPuntos A: " << puntos->getPuntosA();
                qDebug() << "Puntos B: " << query.value(7).toInt();
                qDebug() << "getPuntos B: " << puntos->getPuntosB();

                //si no es el resultado actual, lo pongo en una lista de modificados
                if(query.value(5).isNull()){
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
//        else if(comp->getModalidad()->getTipoRes() == "Sets")
//        {
//            querystr = generarQuerySets( QString::number(partidos[i]->getId()) );

//            // consulta
//            if(!query.exec(querystr)){
//                qDebug() << "La consulta ha fallado";
//                qDebug() << "La consulta que dio error fue: " << querystr;
//                return NULL;
//            }



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

                        Res* resA = new Res();
                        Res* resB = new Res();
                        resA->setId(query.value(1).toInt());
                        resA->setNombre(query.value(2).toString());
//                        resB->setId(query.value(3).toString());
                        resB->setNombre(query.value(4).toString());

                        sets->setResultadoA(resA);
                        sets->setResultadoB(resB);

                        //lo seteo con sus correspondientes "Set"

                        sets->setSets(grupoSet);
                        grupoSet.clear();

                        //si no es el resultado actual, lo pongo en una lista de modificados
                        if(query.value(5).isNull()){
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
                set->setNro_set(query.value(6).toInt());
                set->setPuntosA(query.value(7).toInt());
                set->setPuntosB(query.value(8).toInt());

                grupoSet.push_back(set);

                //fin while()
            }

            //repito por ultima vez el codigo para guardar el ultimo Resultado

            //creo un resultado de tipo "Sets"
            Sets *sets = new Sets;

            //lo seteo con los atributos de cualquier Resultado
            sets->setId(query.value(0).toInt());


            Res* resA = new Res();
            Res* resB = new Res();
            resA->setId(query.value(1).toInt());
            resA->setNombre(query.value(2).toString());
//            resB->setId(query.value(3).toString());
            resB->setNombre(query.value(4).toString());

            sets->setResultadoA(resA);
            sets->setResultadoB(resB);

            //lo seteo con sus correspondientes "Set"
            sets->setSets(grupoSet);

            //si no es el resultado actual, lo pongo en una lista de modificados
            if(query.value(5).isNull()){
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
//        else
//        {
//            qDebug() << "El tipo de resultado no coincide con 'Resultado', 'Puntos' o 'Sets'";
//        }


        //fin for("para cada partido")
//    }


    //seteo competencia con sus partidos y resultados
//    comp->setPartidos(partidos);


//    return comp;
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
int GestorBaseDatos::armarQuerySave(QString tabla, const QVector<Atributo> &atributos){

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
    SELECT R.id_resultado, TRA.id_tipo_resultado, TRA.nombre, TRB.id_tipo_resultado, TRB.nombre, R.partido_actual
    FROM Resultado R, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            TRA.id_tipo_resultado = R.ResultadoA AND
            TRB.id_tipo_resultado = R.ResultadoB

*/

    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual";
    querystr += " FROM Resultado R, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = " +  partidoId + " OR R.partido_modificado = "+ partidoId +")";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";

    return querystr;
}


QString GestorBaseDatos::generarQueryPuntos(QString partidoId) const{
    /**
    SELECT R.id_resultado, TRA.id_tipo_resultado, TRA.nombre, TRB.id_tipo_resultado, TRB.nombre, R.partido_actual, P.puntosA, P.puntosB
    FROM Resultado R, Puntos P, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            R.id_resultado = P.id_resultado AND
            TRA.id_tipo_resultado = R.ResultadoA AND
            TRB.id_tipo_resultado = R.ResultadoB

*/

    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual, P.puntosA, P.puntosB";
    querystr += " FROM Resultado R, Puntos P, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = " +  partidoId + " OR R.partido_modificado = "+ partidoId +")";
    querystr += " AND R.id_resultado = P.id_resultado";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";

    return querystr;
}


QString GestorBaseDatos::generarQuerySets(QString partidoId) const{
    /**
    SELECT R.id_resultado, TRA.id_tipo_resultado, TRA.nombre, TRB.id_tipo_resultado, TRB.nombre, R.partido_actual, S.nro_set, S.puntosA, S.puntosB
    FROM Resultado R, Sets S, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            R.id_resultado = S.id_resultado AND
            TRA.id_tipo_resultado = R.ResultadoA AND
            TRB.id_tipo_resultado = R.ResultadoB
    ORDER BY R.id_resultado, S.nro_set ASC*/

    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual, S.nro_set, S.puntosA, S.puntosB";
    querystr += " FROM Resultado R, Sets S, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = " +  partidoId + " OR R.partido_modificado = "+ partidoId +")";
    querystr += " AND R.id_resultado = S.id_resultado";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";
    querystr += " ORDER BY R.id_resultado, S.nro_set ASC";

    return querystr;
}
