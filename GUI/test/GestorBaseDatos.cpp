/**
 * Project Pegaso
 */


#include "GestorBaseDatos.h"

/**
 * GestorBaseDatos implementation
 */


GestorBaseDatos::GestorBaseDatos()
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




QVector<Competencia *> GestorBaseDatos::getCompetenciasLazy(const DtoGetCompetencia *dto) const{

    /*Consulta usada en este método:

SELECT C.id_competencia, C.nombre, D.id_deporte, D.id_deporte, TM.nombre, TM.id_tipo_modalidad,
    E.nombre, E.id_estado
FROM Competencia C, Deporte D, Modalidad M, Tipo_modalidad TM, Estado E, Usuario U
WHERE C.id_deporte = D.id_deporte AND
    C.id_modalidad = M.id_modalidad AND
    M.id_tipo_modalidad = TM.id_tipo_modalidad AND
    C.id_estado = E.id_estado AND
    C.id_usuario = U.id_usuario AND

    U.email = emailP AND
    M.id_tipo_modalidad = id_tipo_modalidadP AND
    D.id_deporte = id_deporteP AND
    E.id_estado = id_estadoP AND
    C.nombre LIKE '%nombreP%' AND
    C.borrado = 0
        */

    //armamos la consulta
    QString querystr;

    querystr += "SELECT C.id_competencia, C.nombre, D.nombre, D.id_deporte, TM.nombre, TM.id_tipo_modalidad, E.nombre, E.id_estado ";
    querystr += "FROM Competencia C, Deporte D, Modalidad M, Tipo_modalidad TM, Estado E, Usuario U WHERE ";
    querystr += " C.id_usuario = U.id_usuario";
    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND C.id_deporte = D.id_deporte";
    querystr += " AND C.id_estado = E.id_estado";

    //si una opción de filtrado fue elegida, se la agrega a la consulta
    if(dto->usuario != NULL)
    {
        querystr += " AND U.email = '" + dto->usuario->getEmail() + "' ";
    }

    if(dto->tipoModalidad != NULL)
    {
        querystr += " AND M.id_tipo_modalidad = " + QString::number(dto->tipoModalidad->getId());
    }

    if(dto->deporte != NULL)
    {
        querystr += " AND D.id_deporte = " + QString::number(dto->deporte->getId());
    }

    if(dto->estado != NULL)
    {
        querystr += " AND E.id_estado = " + QString::number(dto->estado->getId());
    }

    if(!dto->nombreCompetencia.isEmpty())
    {
        querystr += " AND C.nombre LIKE '%"+ dto->nombreCompetencia + "%'";
    }

    querystr += " AND C.borrado = 0";


    QSqlQuery query;
    //preparamos la consulta
    query.prepare(querystr);

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        return QVector<Competencia *>();
    }

    QVector<Competencia *> competencias;

    //por cada fila en la tabla resultado, se toman los datos y se crean objetos con ellos
    while (query.next()) {

        Competencia *comp = new Competencia();

        comp->setId(query.value(0).toInt());
        comp->setNombre(query.value(1).toString());

        Deporte *deporte = new Deporte();

        deporte->setNombre(query.value(2).toString());
        deporte->setId(query.value(3).toInt());
        comp->setDeporte(deporte);

        Modalidad *modalidad = new Modalidad();

        TipoModalidad* tipoMod = new TipoModalidad();

        tipoMod->setNombre(query.value(4).toString());
        tipoMod->setId(query.value(5).toInt());
        modalidad->setTipoMod(tipoMod);
        comp->setModalidad(modalidad);

        Estado * est = new Estado();

        est->setNombre(query.value(6).toString());
        est->setId(query.value(7).toInt());

        comp->setEstado(est);

        competencias.push_back(comp);
    }

    return competencias;
}




//declaramos estas instancias del la función template para poder usarlas
template bool GestorBaseDatos::LessThan(Participante *a, Participante *b);
template bool GestorBaseDatos::LessThan(Partido *a, Partido *b);

Competencia *GestorBaseDatos::getCompetenciaFull(int id_comp) const{

    //esta consulta carga COMPETENCIA, MODALIDAD y DEPORTE:

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

    //armamos la consulta
    QString querystr;
    querystr += "SELECT C.nombre, E.id_estado, E.nombre, C.fecha_y_horaB, C.reglamento";
    querystr += ", D.id_deporte, D.nombre, M.id_modalidad, M.pto_partido_ganado, M.pto_presentarse";
    querystr += ", M.pto_empate, M.empate, M.cant_max_sets, TM.id_tipo_modalidad, TM.nombre";
    querystr += ", TR.id_tipo_resultado, TR.nombre";
    querystr += " FROM Competencia C, Modalidad M, Tipo_modalidad TM, Tipo_resultado TR, Deporte D, estado E";
    querystr += " WHERE C.id_competencia = ?";
    querystr += " AND C.id_modalidad = M.id_modalidad";
    querystr += " AND M.id_tipo_modalidad = TM.id_tipo_modalidad";
    querystr += " AND M.id_tipo_resultado = TR.id_tipo_resultado";
    querystr += " AND C.id_deporte = D.id_deporte";
    querystr += " AND E.id_estado = C.id_estado";
    querystr += " AND C.borrado = 0";


    QSqlQuery query;
    //preparamos la consulta
    if(!query.prepare(querystr))
        qDebug() << "no anda el prepare";

    //ligamos a la consulta el valor del id de la competencia
    query.addBindValue(QString::number(id_comp));


    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    //nos posicionamos en la primera fila de la tabla resultado
    if(!query.next()){
        qDebug() << "Error Base de datos: No hay ninguna competencia con el id: "<< id_comp;
        return NULL;
    }

    //tomamos todos los datos de la fila y creamos objetos con ellos
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
    //esta consulta carga las DISPONIBILIDADES

    /*
    SELECT SA.disponibilidad, L.id_lugar, L.nombre, L.descripcion
    FROM Se_asignan SA, Lugar L
    WHERE SA.id_competencia = id_comp AND
        SA.id_lugar = L.id_lugar
            */

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT SA.disponibilidad, L.id_lugar, L.nombre, L.descripcion";
    querystr += " FROM Se_asignan SA, Lugar L WHERE SA.id_competencia = ?";
    querystr += " AND SA.id_lugar = L.id_lugar";

    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id de la competencia
    query.addBindValue(id_comp);

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    QVector<Disponibilidad *> disps;

    //por cada fila de la tabla resultado, tomamos los datos y los cargamos en objetos
    while(query.next()){
        Disponibilidad *disp = new Disponibilidad;

        disp->setDisponibilidad(query.value(0).toInt());

        Lugar *lugar = new Lugar;

        lugar->setId(query.value(1).toInt());
        lugar->setNombre(query.value(2).toString());
        lugar->setDescripcion(query.value(3).toString());

        disp->setLugar(lugar);

        disps.push_back(disp);
    }

    comp->setDisponibilidades(disps);

///______________________________________________________________________________________________________________________
    //esta consulta carga los PARTICIPANTES

/*
SELECT id_participante, imagen, nombre, correo, puntos, pg, pp, pe, tf,
tc, dif
FROM Participante
WHERE id_competencia = id_comp
ORDER BY id_participante ASC
*/

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT id_participante, imagen, nombre, correo, puntos, pg, pp, pe, tf, tc, dif";
    querystr += " FROM Participante WHERE id_competencia = ?";
    querystr += " ORDER BY id_participante ASC";

    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id de la competencia
    query.addBindValue(id_comp);

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    QVector<Participante *> partics;

    //por cada fila en la tabla resultado
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
    //esta consulta carga los HISTORIALES DE MODIFICACION DE PARTICIPANTES

/*
SELECT id_modificacion, nombre, correo, imagen
FROM Historial_participante
WHERE id_participante = id_part
*/

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT id_modificacion, nombre, correo, imagen";
    querystr += " FROM Historial_participante WHERE id_participante = ?";

    //preparamos la consulta
    query.prepare(querystr);

    //para cada participante, cargo sus historiales de modificacion
    for(int i = 0; i < partics.size(); i++){

        //ligamos a la consulta el id de un participante
        query.addBindValue(partics[i]->getId());

        //ejecutamos la consulta
        if(!query.exec()){
            qDebug() << "La consulta ha fallado";
            qDebug() << "La consulta que dio error fue: " << querystr;
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

            return NULL;
        }

        QVector<HistorialParticipante *> hists;

        //por cada fila en la tabla resultado
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
    //esta consulta carga los PARTIDOS

/*
SELECT id_partido, fecha, ronda, id_lugar, equipoA, equipoB
FROM Partido
WHERE id_competencia = id_comp
ORDER BY id_partido ASC
*/

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT id_partido, fecha, ronda, id_lugar, equipoA, equipoB";
    querystr += " FROM Partido WHERE id_competencia = ?";
    querystr += " ORDER BY id_partido ASC";

    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id de la competencia
    query.addBindValue(id_comp);

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    QVector<Partido *> partidos;
    int equipoA, equipoB;

    //por cada fila en la tabla resultado
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

        index = lower_bound(partics.begin(),partics.end(),particAuxPtr, GestorBaseDatos::LessThan<Participante>);

        partido->setEquipoA(*index);

        //Busco el equipoB entre los participantes de la Compentencia y lo relaciono al partido
        particAuxPtr->setId(equipoB);
        index = lower_bound(partics.begin(),partics.end(),particAuxPtr, GestorBaseDatos::LessThan<Participante>);
        partido->setEquipoB(*index);

        partidos.push_back(partido);

    }

///______________________________________________________________________________________________________________________
    //esta consulta carga los RESULTADOS

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

    //preparamos la consulta
    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    for(int i = 0; i < partidos.size(); i++){

        //si el resultado es de tipo Resultado
        if(comp->getModalidad()->getTipoRes()->getNombre() == "Resultado Final")
        {

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            //ejecutamos la consulta
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
        else if(comp->getModalidad()->getTipoRes()->getNombre() == "Por Puntos")
        {

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            //ejecutamos la consulta
            if(!query.exec()){
                qDebug() << "La consulta ha fallado";
                qDebug() << "La consulta que dio error fue: " << querystr;
                qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

                return NULL;
            }


            QVector<Resultado *> resultadosModificados;

            //por cada fila en la tabla de resultado
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
        else if(comp->getModalidad()->getTipoRes()->getNombre() == "Por Sets")
        {

            //conecto el id del partido i a la consulta (la consulta lo usa 2 veces)
            query.addBindValue(partidos[i]->getId());
            query.addBindValue(partidos[i]->getId());

            //ejecutamos la consulta
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

            //por cada fila en la tabla resultado
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

                        //creo un resultado de tipo "Por Sets"
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

            //creo un resultado de tipo "Por Sets"
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
    //esta consulta carga las relaciones de SUCESORES (entre partidos)

    /*
SELECT S.partido_anterior, S.partido_siguiente
FROM Sucesor S, Partido P
WHERE S.partido_anterior = P.id_partido AND
    P.id_competencia = compId
*/

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT S.partido_anterior, S.partido_siguiente FROM Sucesor S, Partido P";
    querystr += " WHERE S.partido_anterior = P.id_partido AND P.id_competencia = ?";

    //preparamos la consulta
    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    //ligamos a la consulta el id de la competencia
    query.addBindValue(comp->getId());

    //ejecutamos la consulta
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

    //por cada fila de la tabla resultado, creamos una asociación entre partidos que se suceden
    while(query.next())
    {
        int partido_anterior_id = query.value(0).toInt();
        int partido_siguiente_id = query.value(1).toInt();

        //Busco el primer partido de la relacion Sucesor, entre los partidos de la Compentencia
        partidoAuxPtr->setId(partido_anterior_id);
        index = lower_bound(partidos.begin(),partidos.end(),partidoAuxPtr, GestorBaseDatos::LessThan<Partido>);
        partido_anterior = *index;

        //Busco el segundo partido de la relacion Sucesor, entre los partidos de la Compentencia
        //y lo relaciono al partido primer partido como su sucesor
        partidoAuxPtr->setId(partido_siguiente_id);
        index = lower_bound(partidos.begin(),partidos.end(),partidoAuxPtr, GestorBaseDatos::LessThan<Partido>);
        partido_anterior->addSucesor(*index);
    }

    //le indico que setee su fecha actual
    comp->getFechaActual();

    return comp;
}




bool GestorBaseDatos::saveParticipantes(QVector<Participante *> participantes, int id_comp)
{
    Atributo id_externoA("id_competencia",QString::number(id_comp));
    return this->save(participantes, &id_externoA);
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
    SELECT R.id_resultado, TRA.id_res, TRA.nombre, TRB.id_res, TRB.nombre, R.partido_actual
    FROM Resultado R, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            TRA.id_res = R.resultadoA AND
            TRB.id_res = R.resultadoB
*/

    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual";
    querystr += " FROM Resultado R, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND RA.id_res = R.resultadoA";
    querystr += " AND RB.id_res = R.resultadoB ";

    return querystr;
}




QString GestorBaseDatos::generarQueryPuntos() const{
    /**
    SELECT R.id_resultado, TRA.id_res, TRA.nombre, TRB.id_res, TRB.nombre, R.partido_actual, P.puntosA, P.puntosB
    FROM Resultado R, Puntos P, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            R.id_resultado = P.id_resultado AND
            TRA.id_res = R.resultadoA AND
            TRB.id_res = R.resultadoB
*/
    //armamos la consulta
    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual, P.puntosA, P.puntosB";
    querystr += " FROM Resultado R, Puntos P, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND R.id_resultado = P.id_resultado";
    querystr += " AND RA.id_res = R.resultadoA";
    querystr += " AND RB.id_res = R.resultadoB ";

    return querystr;
}


QString GestorBaseDatos::generarQuerySets() const{
    /**
    SELECT R.id_resultado, TRA.id_res, TRA.nombre, TRB.id_res, TRB.nombre, R.partido_actual, S.nro_set, S.puntosA, S.puntosB
    FROM Resultado R, Sets S, Tipo_resultado TRA, Tipo_resultado TRB
    WHERE   (R.partido_actual = id_partido OR
            R.partido_modificado = id_partido) AND
            R.id_resultado = S.id_resultado AND
            TRA.id_res = R.resultadoA AND
            TRB.id_res = R.resultadoB
    ORDER BY R.id_resultado, S.nro_set ASC*/

    //armamos la consulta
    QString querystr;
    querystr += "SELECT R.id_resultado, RA.id_res, RA.nombre, RB.id_res, RB.nombre, R.partido_actual, S.nro_set, S.puntosA, S.puntosB";
    querystr += " FROM Resultado R, Sets S, res RA, res RB ";
    querystr += " WHERE  (R.partido_actual = ? OR R.partido_modificado = ?)";
    querystr += " AND R.id_resultado = S.id_resultado";
    querystr += " AND RA.id_res = R.resultadoA";
    querystr += " AND RB.id_res = R.resultadoB ";
    querystr += " ORDER BY R.id_resultado, S.nro_set ASC";

    return querystr;
}


Usuario *GestorBaseDatos::cargarUsuario(QString correo)
{
    /*
SELECT U.id_usuario, U.nro_doc, D.id_tipo_doc, D.nombre, U.password, U.nombre,
    U.apellido, L.id_localidad, L.nombre
FROM Usuario U, Tipo_doc D, Localidad L
WHERE U.email = correo AND
    U.id_tipo_doc = D.id_tipo_doc AND
    U.id_localidad = U.id_localidad
    */

    //armamos la consulta
    QString querystr;
    querystr += "SELECT U.id_usuario, U.nro_doc, D.id_tipo_doc, D.nombre, U.password, U.nombre, U.apellido";
    querystr += ", L.id_localidad, L.nombre";
    querystr += " FROM Usuario U, Tipo_doc D, Localidad L";
    querystr += " WHERE U.email = ?";
    querystr += " AND U.id_tipo_doc = D.id_tipo_doc";
    querystr += " AND U.id_localidad = U.id_localidad";

    QSqlQuery query;

    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta la dirección de correo del usuario
    query.addBindValue(correo);

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return NULL;
    }

    Usuario *user;

    //si hay un usuario con ese correo
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

    }
    //si no hay un usuario con ese correo
    else
    {
        return NULL;
    }


    /*Consulta para cargar los LUGARES de este usuario:
     *
SELECT L.id_lugar, L.nombre, L.descripcion
FROM Lugar L
WHERE L.id_usuario = userId AND
    L.borrado = 0*/

    querystr.clear();

    //armamos la consulta
    querystr += "SELECT L.id_lugar, L.nombre, L.descripcion";
    querystr += " FROM Lugar L WHERE L.id_usuario = ? AND L.borrado = 0";

    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id del usuario
    query.addBindValue(user->getId());

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return user;
    }

    QVector<Lugar *> lugares;

    //por cada fila de la tabla resultado
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




bool GestorBaseDatos::saveUsuario(Usuario *usuario)
{
    //armamos la consulta
    QString queryStr = "INSERT OR REPLACE INTO Usuario(id_usuario,email,nro_doc,id_tipo_doc,password,nombre,apellido,id_localidad) ";
    queryStr += " VALUES (?,?,?,?,?,?,?,?)";

    QSqlQuery query;
    //preparamos la consulta
    query.prepare(queryStr);

    //ligamos todos los valores a la consulta
    query.addBindValue(usuario->getId());
    query.addBindValue(usuario->getEmail());
    query.addBindValue(usuario->getNro_doc());
    query.addBindValue(usuario->getDoc()->getId());
    query.addBindValue(usuario->getPassword());
    query.addBindValue(usuario->getNombre());
    query.addBindValue(usuario->getApellido());
    query.addBindValue(usuario->getLocalidad()->getId());

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << queryStr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        return false;
    }
    return true;
}



QVector<Deporte *> GestorBaseDatos::getDeportes()
{
    /*SELECT D.id_deporte, D.nombre
FROM Deporte D*/

    QString querystr;
    //armamos la consulta
    querystr += "SELECT D.id_deporte, D.nombre FROM Deporte D";

    QSqlQuery query;

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Deporte *>();
    }

    QVector<Deporte *> deportes;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT P.id_pais, P.nombre FROM Pais P";

    QSqlQuery query;

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Pais *>();
    }

    QVector<Pais *> paises;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT PR.id_provincia, PR.nombre FROM Provincia PR WHERE PR.id_pais = ?";

    QSqlQuery query;
    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id del pais
    query.addBindValue(pais->getId());

    qDebug()<<"id pais "<<pais->getId();

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Provincia *>();
    }

    QVector<Provincia *> provincias;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT L.id_localidad, L.nombre FROM Localidad L WHERE L.id_provincia = ?";

    QSqlQuery query;
    //preparamos la consulta
    query.prepare(querystr);

    //ligamos a la consulta el id de la provincia
    query.addBindValue(provincia->getId());

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Localidad *>();
    }

    QVector<Localidad *> localidades;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT E.id_estado, E.nombre FROM Estado E";

    QSqlQuery query;

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Estado *>();
    }

    QVector<Estado *> estados;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT TM.id_tipo_modalidad, TM.nombre FROM Tipo_modalidad TM";

    QSqlQuery query;

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<TipoModalidad *>();
    }

    QVector<TipoModalidad *> tmodalidades;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT L.id_lugar, L.nombre, L.descripcion FROM Lugar L WHERE L.id_usuario = ?";
    querystr += " AND L.borrado = 0";

    QSqlQuery query;
    //preparamos la consulta
    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    //ligamos a la consulta el id del usuario
    query.addBindValue(user->getId());

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<Lugar *>();
    }

    QVector<Lugar *> lugares;

    //por cada fila de la tabla resultado
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
    //armamos la consulta
    querystr += "SELECT TR.id_tipo_resultado, TR.nombre FROM Tipo_resultado TR";

    QSqlQuery query;

    //ejecutamos la consulta
    if(!query.exec(querystr)){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return QVector<TipoResultado *>();
    }

    QVector<TipoResultado *> tiposRes;

    //por cada fila de la tabla resultado
    while(query.next())
    {
        TipoResultado *tipo = new TipoResultado();

        tipo->setId(query.value(0).toInt());
        tipo->setNombre(query.value(1).toString());

        tiposRes.push_back(tipo);
    }

    return tiposRes;
}

bool GestorBaseDatos::eliminarPartidos(Competencia *comp){
    /*
     * DELETE FROM Partido
     * WHERE id_competencia = compId
    */

    int compId = comp->getId();

    QString querystr;
    //armamos la consulta
    querystr += "DELETE FROM Partido WHERE id_competencia = ?";

    QSqlQuery query;
    //preparamos la consulta
    if(!query.prepare(querystr))
        qDebug() << "falla el prepare";

    //ligamos a la consulta el id de la competencia
    query.addBindValue(compId);

    //ejecutamos la consulta
    if(!query.exec()){
        qDebug() << "La consulta ha fallado";
        qDebug() << "La consulta que dio error fue: " << querystr;
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        return false;
    }

    return true;
}
