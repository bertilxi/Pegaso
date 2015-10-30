#ifndef GESTORBASEDATOSSAVEESPECIALES
#define GESTORBASEDATOSSAVEESPECIALES

//recordar quitar esto
#include "Puntos.h"
#include "Sets.h"
#include "GestorUsuarios.h"

/**
 * @brief persiste un objeto Competencia
 * @param comp la competencia a persistir
 * @param usuarioId id del usuario al que pertenece la competencia
 * @return true si tuvo exito, false si fallo
 */
bool GestorBaseDatos::saveCompetencia(Competencia *comp, int usuarioId){

    bool status = true;

    //guardo modalidad
    Modalidad *mod = comp->getModalidad();
    status &= this->save(QVector<Modalidad *>(1,mod));

    //guardo los atributos simples de competencia
    Atributo usuarioIdAtributo("id_usuario",QString::number(usuarioId));
    status &= this->save(QVector<Competencia *>(1,comp), &usuarioIdAtributo);

    //guardo las disponibilidades
    QVector<Disponibilidad *> disps = comp->getDisponibilidades();
    Atributo competenciaId("id_competencia",QString::number(comp->getId()));
    status &= this->save(disps, &competenciaId);

    //guardo los participantes
    QVector<Participante *> participantes = comp->getParticipantes();
    status &= this->save(participantes, &competenciaId);

    //guardo los historiales de cada participante
    for(int i = 0; i < participantes.size(); i++){
        Atributo participanteId("id_participante",QString::number(participantes[i]->getId()));
        status &= this->save(participantes[i]->getHistorial(), &participanteId);
    }

    //guardo los partidos
    QVector<Partido *> partidos = comp->getPartidos();
    status &= this->save(partidos, &competenciaId);

    for(int i = 0; i < partidos.size(); i++){

        //guardo los resultados de cada partido
        status &= this->saveResultado(partidos[i]->getActual(), Atributo("partido_actual",QString::number(partidos[i]->getId())));

        //guardo el historial de cada partido
        QVector<Resultado *> modificados = partidos[i]->getModificado();
        for(int j = 0; j < modificados.size(); j++){
            status &= this->saveResultado(modificados[j], Atributo("partido_modificado",QString::number(partidos[i]->getId())));
        }
    }

    for(int i = 0; i < partidos.size(); i++){
        QVector<Partido *> sucesores = partidos[i]->getSucesores();
        for(int j = 0; j < sucesores.size(); j++){
            status &= this->saveRelacion(partidos[i],sucesores[j]);
        }
    }
    return status;
}

bool GestorBaseDatos::saveResultado(Resultado *resultado, Atributo partidoId){
    bool status = true;

    Puntos *puntos = dynamic_cast<Puntos *>(resultado);
    if(puntos != NULL)  //si es de clase Puntos
    {
        status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
        Atributo resultadoId("id_resultado",QString::number(resultado->getId()));
        status &= this->save(QVector<Puntos *>(1,puntos), &resultadoId);
    }
    else
    {
        Sets *sets = dynamic_cast<Sets *>(resultado);
        if(sets != NULL)    //si es de clase Sets
        {
            status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
            Atributo resultadoId("id_resultado",QString::number(resultado->getId()));
            status &= this->save(sets->getSets(), &resultadoId);
        }
        else    //si es de clase Resultado
        {
            status &= this->save(QVector<Resultado *>(1,resultado), &partidoId);
        }
    }
//-----------------------------------------------------------------------------------------------

    ///Problema: getTable() no es virtual. Siempre devolverá "Resultado".
/*
    switch(tabla[0].toLatin1()){
    case 'R': //"Resultado"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        break;
    case 'P': //"Puntos"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        status &= this->save(QVector<Puntos *>(1,dynamic_cast<Puntos *>(resultado)), Atributo("id_resultado",resultado->getId()));
        break;
    case 'S': //"Sets"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        QVector<Sets *> sets = dynamic_cast<Sets *>(resultado)->getSets();
        status &= this->save(sets, Atributo("id_resultado",resultado->getId()));
        break;
    }*/
    return status;
}

#endif // GESTORBASEDATOSSAVEESPECIALES

