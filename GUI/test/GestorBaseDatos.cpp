/**
 * Project Pegaso
 */


#include "GestorBaseDatos.h"

/**
 * GestorBaseDatos implementation
 */



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
    C.borrado = 0 AND
    C.nombre LIKE '%nombreP%'
        */

    QString querystr;

    querystr += "SELECT C.id_competencia, C.nombre, D.nombre, D.id_deporte, TM.nombre, TM.id_tipo_modalidad, E.nombre, E.id_estado ";
    querystr += "FROM Competencia C, Deporte D, Modalidad M, Tipo_modalidad TM, Estado E, Usuario U WHERE ";

    bool primeraCondicion = true;
    if(dto->usuario != NULL)
    {
        querystr += "U.email = '" + dto->usuario->getEmail() + "' ";
        primeraCondicion = false;
    }

    if(dto->tipoModalidad != NULL)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "M.id_tipo_modalidad = " + QString::number(dto->tipoModalidad->getId());
        primeraCondicion = false;
    }

    if(dto->deporte != NULL)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "D.id_deporte = " + QString::number(dto->deporte->getId());
        primeraCondicion = false;
    }

    if(dto->estado != NULL)
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "E.id_estado = " + QString::number(dto->estado->getId());
        primeraCondicion = false;
    }

    if(!dto->nombreCompetencia.isEmpty())
    {
        if(!primeraCondicion) {querystr += " AND ";}
        querystr += "C.nombre LIKE '%"+ dto->nombreCompetencia + "%'";
        primeraCondicion = false;
    }

    if(!primeraCondicion){
        querystr += " AND";
    }
    querystr += " C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND C.id_deporte = D.id_deporte";
    querystr += " AND E.id_estado = C.id_estado";

    QSqlQuery query;

    query.prepare(querystr);
//    query.addBindValue(dto->nombreCompetencia);

    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
    }

    QVector<Competencia *> competencias;
int debug =0;
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
        deporte->setNombre(query.value(2).toString());
        deporte->setId(query.value(3).toInt());
        comp->setDeporte(deporte);

        Modalidad *modalidad = new (std::nothrow) Modalidad;
        if(modalidad == NULL){
            qDebug() << "No se pudo alocar memoria para Modalidad";
            ///Es necesario destruir la competencia
            return QVector<Competencia *>();
        }

        TipoModalidad* tipoMod = new TipoModalidad();

        tipoMod->setNombre(query.value(4).toString());
        tipoMod->setId(query.value(5).toInt());
        qDebug() << "modalidad 3";
        qDebug() <<tipoMod->getId();
        qDebug() <<tipoMod->getNombre();


        modalidad->setTipoMod(tipoMod);
        comp->setModalidad(modalidad);

        Estado * est = new Estado();

//        est->setId(query.value(4).toInt());
        est->setNombre(query.value(6).toString());
        est->setId(query.value(7).toInt());

        comp->setEstado(est);

        competencias.push_back(comp);
        qDebug()<<debug++;

    }

    return competencias;
}

Competencia *GestorBaseDatos::getCompetenciaFull(int id_comp) const{

    //CARGA COMPETENCIA, MODALIDAD Y DEPORTE

/*
SELECT C.nombre, E.id_estado, E.nombre, C.fecha_y_horaB, C.reglamento,
    D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse,
    M.pto_empate, M.empate ,M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre,
    TR.id_tipo_resultado, TR.nombre
FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR,
    Deporte D, estado E
WHERE C.id_competencia = id_comp AND
    C.id_modalidad = M.id_modalidad AND
    M.id_tipo_modalidad = TM.id_tipo_modalidad AND
    C.id_tipo_resultado = TR.id_tipo_resultado AND
    C.id_deporte = D.id_deporte AND
    E.id_estado = C.id_estado AND
    C.borrado = 0
*/


    QString querystr;
    querystr += "SELECT C.nombre, E.id_estado, E.nombre, C.fecha_y_horaB, C.reglamento";
    querystr += ", D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse";
    querystr += ", M.pto_empate, M.empate, M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre";
    querystr += ", TR.id_tipo_resultado, TR.nombre";
    querystr += " FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D, estado E";
    querystr += " WHERE C.id_competencia = " + QString::number(id_comp);
    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND M.id_tipo_resultado = TR.id_tipo_resultado";
    querystr += " AND C.id_deporte = D.id_deporte";
    querystr += " AND E.id_estado = C.id_estado";
    querystr += " AND C.borrado = 0";

    QSqlQuery query;



    // consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

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

    est->setId(query.value(1).toInt());
    est->setNombre(query.value(2).toString());

    comp->setEstado(est);

    comp->setFecha_y_horaB(query.value(3).toString());
    comp->setBorrado(false);
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
    mod->setEmpate((bool)query.value(11).toInt());
    mod->setCant_max_sets(query.value(12).toInt());

    TipoModalidad* tipoMod = new TipoModalidad();

    tipoMod->setId(query.value(13).toInt());
    tipoMod->setNombre(query.value(14).toString());

    mod->setTipoMod(tipoMod);

    TipoResultado* tipoRes = new TipoResultado();

    tipoRes->setId(query.value(15).toInt());
    tipoRes->setNombre(query.value(16).toString());

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
    querystr += " FROM Se_asignan SA WHERE SA.id_competencia = ?";

    query.prepare(querystr);
    query.addBindValue(id_comp);

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

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
WHERE id_competencia = id_comp
ORDER BY id_participante ASC
*/

    querystr.clear();

    querystr += "SELECT id_participante, imagen, nombre, correo, puntos, pg, pp, pe, tf, tc, dif";
    querystr += " FROM Participante WHERE id_competencia = ?";
    querystr += " ORDER BY id_participante ASC";

    query.prepare(querystr);
    query.addBindValue(id_comp);

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

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

    querystr.clear();

    querystr += "SELECT id_modificacion, nombre, correo, imagen";
    querystr += " FROM Historial_participante WHERE id_participante = ?";

    query.prepare(querystr);

    //para cada participante, cargo sus historiales de modificacion
    for(int i = 0; i < partics.size(); i++){

        query.addBindValue(partics[i]->getId());

        // consulta
        if(!query.exec()){
            qDebug() << "La consulta ha fallado";
            qDebug() << "La consulta que dio error fue: " << querystr;
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

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
ORDER BY id_partido ASC
*/

    querystr.clear();

    querystr += "SELECT id_partido, fecha, ronda, id_lugar, equipoA, equipoB";
    querystr += " FROM Partido WHERE id_competencia = ?";
    querystr += " ORDER BY id_partido ASC";

    query.prepare(querystr);
    query.addBindValue(id_comp);

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

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

        index = lower_bound(partics.begin(),partics.end(),particAuxPtr, GestorBaseDatos::LessThan);

        partido->setEquipoA(*index);

        //Busco el equipoB entre los participantes de la Compentencia y lo relaciono al partido
        particAuxPtr->setId(equipoB);
        index = lower_bound(partics.begin(),partics.end(),particAuxPtr, GestorBaseDatos::LessThan);
        partido->setEquipoB(*index);

        partidos.push_back(partido);

    }

///______________________________________________________________________________________________________________________
    //CARGA RESULTADOS

    switch(comp->getModalidad()->getTipoRes()->getId())
    {
    case 1: //Resultado
        querystr = generarQueryResultado();
        break;
    case 2: //Puntos
        querystr = generarQueryPuntos();
        break;
    case 3: //Sets
        querystr = generarQuerySets();
        break;
    default:
        qDebug() << "El tipo de resultado no coincide con 'Resultado', 'Puntos' o 'Sets'";
    }

    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    for(int i = 0; i < partidos.size(); i++){

        //si el resultado es de tipo Resultado
        if(comp->getModalidad()->getTipoRes()->getNombre() == "Resultado")
        {

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            // consulta
            if(!query.exec()){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

                return NULL;
            }

            QVector<Resultado *> resultadosModificados;
            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 id_res A       (ej: id relacionada con "gano")
                 * 2 nombre res A   (ej: "gano")
                 * 3 id_res B
                 * 4 nombre res B
                 * 5 partido_actual (es o no es el actual?)
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
                if(query.value(5).isNull()){
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

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            // consulta
            if(!query.exec()){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

                return NULL;
            }


            QVector<Resultado *> resultadosModificados;
            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 id_res A       (ej: id relacionada con "gano")
                 * 2 nombre res A   (ej: "gano")
                 * 3 id_res B
                 * 4 nombre res B
                 * 5 partido_actual (es o no es el actual?)
                 * 6 puntos A
                 * 7 puntos B
                 * */

                Puntos *puntos = new Puntos;
                puntos->setId(query.value(0).toInt());

                Res* resA = new Res();
                Res* resB = new Res();
                resA->setId(query.value(1).toInt());
                resA->setNombre(query.value(2).toString());

                resB->setId(query.value(3).toInt());
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
        else if(comp->getModalidad()->getTipoRes()->getNombre() == "Sets")
        {

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            // consulta
            if(!query.exec()){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

                return NULL;
            }



            QVector<Set *> grupoSet;
            QVector<Resultado *> resultadosModificados;
            bool primerResultado = true;
            int resultadoActual = -1000;

            while(query.next()){
                /*
                 * 0 id_resultado
                 * 1 id_res A       (ej: id relacionada con "gano")
                 * 2 nombre res A   (ej: "gano")
                 * 3 id_res B
                 * 4 nombre res B
                 * 5 partido_actual (es o no es el actual?)
                 * 6 nro_set
                 * 7 puntosA
                 * 8 puntosB
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
                        resB->setId(query.value(3).toInt());
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
            resB->setId(query.value(3).toInt());
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
        else
        {
            qDebug() << "El tipo de resultado no coincide con 'Resultado', 'Puntos' o 'Sets'";
        }


        //fin for("para cada partido")
    }


    //seteo competencia con sus partidos y resultados
    comp->setPartidos(partidos);

///______________________________________________________________________________________________________________________
    //CARGA SUCESORES

/*
SELECT S.partido_anterior, S.partido_siguiente
FROM Sucesor S, Partido P
WHERE S.partido_anterior = P.id_partido AND
    P.id_competencia = compId
    */

    querystr.clear();

    querystr += "SELECT S.partido_anterior, S.partido_siguiente FROM Sucesor S, Partido P";
    querystr += " WHERE S.partido_anterior = P.id_partido AND P.id_competencia = ?";

    if(!query.prepare(querystr))
    qDebug() << "falla el prepare";

    query.addBindValue(comp->getId());

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }


    Partido partidoAux;
    Partido *partidoAuxPtr = &partidoAux;
    Partido *partido_anterior;
    QVector<Partido *>::iterator index;

    while(query.next())
    {
        int partido_anterior_id = query.value(0).toInt();
        int partido_siguiente_id = query.value(1).toInt();

        //Busco el primer partido de la relacion Sucesor, entre los partidos de la Compentencia
        partidoAuxPtr->setId(partido_anterior_id);
        index = lower_bound(partidos.begin(),partidos.end(),partidoAuxPtr, GestorBaseDatos::LessThan);
        partido_anterior = *index;

        //Busco el segundo partido de la relacion Sucesor, entre los partidos de la Compentencia
        //y lo relaciono al partido primer partido como su sucesor
        partidoAuxPtr->setId(partido_siguiente_id);
        index = lower_bound(partidos.begin(),partidos.end(),partidoAuxPtr, GestorBaseDatos::LessThan);
        partido_anterior->addSucesor(*index);
    }



    return comp;
}





//temporal
bool GestorBaseDatos::save(QVector<Participante *> participantes, int id_externo){
    Atributo id_externoA("id_competencia",QString::number(id_externo));
    return this->save(participantes, &id_externoA);
}



/**
 * @param obj
 * @param filtros
 * @brief Ejecuta una consulta en la base de datos con filtros como parametros en select
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
int GestorBaseDatos::lastCompId()
{
    QString str = "select seq from sqlite_sequence where name = 'Competencia'";
    QSqlQuery query;
    query.exec(str);
    while(query.next()){
        qDebug()<<"id competencia";
        qDebug()<<query.value(0).toInt();
        return query.value(0).toInt();
    }
}
int GestorBaseDatos::lastModId()
{
    QString str = "select seq from sqlite_sequence where name = 'Modalidad'";
    QSqlQuery query;
    query.exec(str);
    while(query.next()){
        return query.value(0).toInt();
    }
}

int GestorBaseDatos::armarQuerySave(QString tabla, const QVector<Atributo> &atributos){

    QString querystr;

    querystr = "insert or replace into " + tabla + " ( " ;

    int j;
    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += atributos[j].campo + " , " ;
    }
    querystr += atributos[j].campo + ") values (" ;

    for (j = 0; j < atributos.size()-1; ++j)
    {
        querystr += "?,";
    }
    querystr += "?) ";

    QSqlQuery query;
    query.prepare(querystr);
    for(j = 0; j < atributos.size(); ++j){
        query.addBindValue(atributos[j].valor);
    }

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        qDebug() << "La consulta que dio error fue: " << querystr;
        return -1;
    }

    return query.lastInsertId().toInt();
}


QString GestorBaseDatos::generarQueryResultado() const{
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
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";

    return querystr;
}


QString GestorBaseDatos::generarQueryPuntos() const{
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
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND R.id_resultado = P.id_resultado";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";

    return querystr;
}


QString GestorBaseDatos::generarQuerySets() const{
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
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND R.id_resultado = S.id_resultado";
    querystr += " AND RA.id_tipo_resultado = R.ResultadoA";
    querystr += " AND RB.id_tipo_resultado = R.ResultadoB ";
    querystr += " ORDER BY R.id_resultado, S.nro_set ASC";

    return querystr;
}


Usuario *GestorBaseDatos::cargarUsuario(QString correo)
{
    /*SELECT U.id_usuario, U.nro_doc, D.id_tipo_doc, D.nombre, U.password, U.nombre,
    U.apellido, L.id_localidad, L.nombre, PR.id_provincia, PR.nombre,
    PA.id_pais, PA.nombre
FROM Usuario U, Tipo_doc D, Localidad L, Provincia PR, Pais PA
WHERE U.email = correo AND
    U.id_tipo_doc = D.id_tipo_doc AND
    U.id_localidad = U.id_localidad AND
    L.id_provincia = PR.id_provincia AND
    PR.id_pais = PA.id_pais*/

    QString querystr;
    querystr += "SELECT U.id_usuario, U.nro_doc, D.id_tipo_doc, D.nombre, U.password, U.nombre, U.apellido";
    querystr += ", L.id_localidad, L.nombre, PR.id_provincia, PR.nombre, PA.id_pais, PA.nombre";
    querystr += " FROM Usuario U, Tipo_doc D, Localidad L, Provincia PR, Pais PA";
    querystr += " WHERE U.email = ?";
    querystr += " AND U.id_tipo_doc = D.id_tipo_doc";
    querystr += " AND U.id_localidad = U.id_localidad";
    querystr += " AND L.id_provincia = PR.id_provincia";
    querystr += " AND PR.id_pais = PA.id_pais";

    QSqlQuery query;

    query.prepare(querystr);
    query.addBindValue(correo);

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    Usuario *user;

    if(query.next())
    {
        user = new Usuario();

        user->setEmail(correo);
        user->setId(query.value(0).toInt());
        user->setNro_doc(query.value(1).toString());

        Doc *doc = new Doc();
        doc->setId(query.value(2).toInt());
        doc->setTipo(query.value(3).toString());

        user->setDoc(doc);

        user->setPassword(query.value(4).toByteArray());
        user->setNombre(query.value(5).toString());
        user->setApellido(query.value(6).toString());

        Localidad *loc = new Localidad();
        loc->setId(query.value(7).toInt());
        loc->setNombre(query.value(8).toString());

        user->setLocalidad(loc);

        Provincia *prov = new Provincia();
        prov->setId(query.value(9).toInt());
        prov->setNombre(query.value(10).toString());

        user->setProvincia(prov);

        Pais *pais = new Pais();
        pais->setId(query.value(11).toInt());
        pais->setNombre(query.value(12).toString());

        user->setPais(pais);
    }
    else
    {
        qDebug() << "Error: no hay usuario con correo: " << correo;

        return NULL;
    }

    /*SELECT L.id_lugar, L.nombre, L.descripcion
FROM Lugar L
WHERE L.id_usuario = userId AND
    L.borrado = 0*/

    querystr.clear();

    querystr += "SELECT L.id_lugar, L.nombre, L.descripcion";
    querystr += " FROM Lugar L WHERE L.id_usuario = ? AND L.borrado = 0";

    query.prepare(querystr);
    query.addBindValue(user->getId());

    // consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return user;
    }

    QVector<Lugar *> lugares;
    while(query.next())
    {
        Lugar *lugar = new Lugar();
        lugar->setId(query.value(0).toInt());
        lugar->setNombre(query.value(1).toString());

        lugares.push_back(lugar);
    }

    user->setLugares(lugares);

    return user;
}

Usuario *GestorBaseDatos::saveUsuario(Usuario *usuario)
{

}

GestorBaseDatos::GestorBaseDatos(QString dbs)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("pegaso.db");


        if(db.open()){
            qDebug()<<"Se ha conectado la Base de Datos";
        }
        else{
            qDebug()<<"Error al conectar la Base de Datos";
        }
}

QVector<Deporte *> GestorBaseDatos::getDeportes()
{
    /*SELECT D.id_deporte, D.nombre
FROM Deporte D*/

    QString querystr;
    querystr += "SELECT D.id_deporte, D.nombre FROM Deporte D";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Deporte *>();
    }

    QVector<Deporte *> deportes;

    while(query.next())
    {
        Deporte *dep = new Deporte();
        dep->setId(query.value(0).toInt());
        dep->setNombre(query.value(1).toString());

        deportes.push_back(dep);
    }

    return deportes;
}

QVector<Pais *> GestorBaseDatos::getPaises()
{
    /*SELECT P.id_pais, P.nombre
FROM Pais P*/

    QString querystr;
    querystr += "SELECT P.id_pais, P.nombre FROM Pais P";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Pais *>();
    }

    QVector<Pais *> paises;

    while(query.next())
    {
        Pais *pais = new Pais;
        pais->setId(query.value(0).toInt());
        pais->setNombre(query.value(1).toString());

        paises.push_back(pais);
    }

    return paises;
}

QVector<Provincia *> GestorBaseDatos::getProvincias(Pais *pais)
{
    /*SELECT PR.id_provincia, PR.nombre
FROM Provincia PR
WHERE PR.id_pais = paisId*/

    QString querystr;
    querystr += "SELECT PR.id_provincia, PR.nombre FROM Provincia PR WHERE PR.id_pais = ?";

    QSqlQuery query;
    query.prepare(querystr);
    query.addBindValue(pais->getId());

    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Provincia *>();
    }

    QVector<Provincia *> provincias;

    while(query.next())
    {
        Provincia *prov = new Provincia();

        prov->setId(query.value(0).toInt());
        prov->setNombre(query.value(1).toString());

        provincias.push_back(prov);
    }

    return provincias;
}

QVector<Localidad *> GestorBaseDatos::getLocalidades(Provincia *provincia)
{
    /*SELECT L.id_localidad, L.nombre
FROM Localidad L
WHERE L.id_provincia = provinciaId*/

    QString querystr;
    querystr += "SELECT L.id_localidad, L.nombre FROM Localidad L WHERE L.id_provincia = ?";

    QSqlQuery query;
    query.prepare(querystr);
    query.addBindValue(provincia->getId());

    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Localidad *>();
    }

    QVector<Localidad *> localidades;

    while(query.next())
    {
        Localidad *loc = new Localidad();

        loc->setId(query.value(0).toInt());
        loc->setNombre(query.value(1).toString());

        localidades.push_back(loc);
    }

    return localidades;
}

QVector<Estado *> GestorBaseDatos::getEstados()
{
    /*SELECT E.id_estado, E.nombre
FROM Estado E*/

    QString querystr;
    querystr += "SELECT E.id_estado, E.nombre FROM Estado E";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Estado *>();
    }

    QVector<Estado *> estados;

    while(query.next())
    {
        Estado *est = new Estado;

        est->setId(query.value(0).toInt());
        est->setNombre(query.value(1).toString());

        estados.push_back(est);
    }

    return estados;
}

QVector<TipoModalidad *> GestorBaseDatos::getTipoModalidades()
{
    /*SELECT TM.id_tipo_modalidad, TM.nombre
FROM Tipo_modalidad TM*/

    QString querystr;
    querystr += "SELECT TM.id_tipo_modalidad, TM.nombre FROM Tipo_modalidad TM";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<TipoModalidad *>();
    }

    QVector<TipoModalidad *> tmodalidades;

    while(query.next())
    {
        TipoModalidad *tmod = new TipoModalidad();

        tmod->setId(query.value(0).toInt());
        tmod->setNombre(query.value(1).toString());

        tmodalidades.push_back(tmod);
    }

    return tmodalidades;
}

QVector<Lugar *> GestorBaseDatos::getLugares(Usuario *user)
{
    /*SELECT L.id_lugar, L.nombre, L.descripcion
FROM Lugar L
WHERE L.id_usuario = userId AND
    L.borrado = 0*/

    QString querystr;
    querystr += "SELECT L.id_lugar, L.nombre, L.descripcion FROM Lugar L WHERE L.id_usuario = ?";
    querystr += " AND L.borrado = 0";

    QSqlQuery query;

    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    query.addBindValue(user->getId());

    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Lugar *>();
    }

    QVector<Lugar *> lugares;

    while(query.next())
    {
        Lugar *lugar = new Lugar();

        lugar->setId(query.value(0).toInt());
        lugar->setNombre(query.value(1).toString());
        lugar->setDescripcion(query.value(2).toString());

        lugares.push_back(lugar);
    }

    return lugares;
}

QVector<TipoResultado *> GestorBaseDatos::getTiposResultado()
{
    /*SELECT TR.id_tipo_resultado, TR.nombre
FROM Tipo_resultado TR*/

    QString querystr;
    querystr += "SELECT TR.id_tipo_resultado, TR.nombre FROM Tipo_resultado TR";

    QSqlQuery query;

    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<TipoResultado *>();
    }

    QVector<TipoResultado *> tiposRes;

    while(query.next())
    {
        TipoResultado *tipo = new TipoResultado();

        tipo->setId(query.value(0).toInt());
        tipo->setNombre(query.value(1).toString());

        tiposRes.push_back(tipo);
    }

    return tiposRes;
}
