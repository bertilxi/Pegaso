#ifndef GESTORBASEDATOSSAVEESPECIALES
#define GESTORBASEDATOSSAVEESPECIALES

//recordar quitar esto
#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Puntos.h"
#include "../Grupo Competencia/Sets.h"
#include "GestorUsuarios.h"
#include <QString>
#include <QVector>

/**
 * @brief persiste un objeto Competencia
 * @param comp la competencia a persistir
 * @return true si tuvo exito, false si fallo
 */
bool GestorBaseDatos::saveCompetencia(Competencia *comp, int usuarioId){

    bool status = true;

    Modalidad *mod = comp->getModalidad();
    status &= this->save(QVector<Modalidad *>(1,mod));    //guardo modalidad

    status &= this->save(QVector<Competencia *>(1,comp), usuarioId);   //guardo los atributos simples de competencia

    QVector<Disponibilidad *> disps = comp->getDisponibilidades();
    status &= this->save(disps, comp->getId());   //guardo las disponibilidades

    QVector<Participante *> participantes = comp->getParticipantes();
    status &= this->save(participantes, comp->getId());   //guardo los participantes

    for(int i = 0; i < participantes.size(); i++){
        //guardo los historiales de cada participante
        status &= this->save(participantes[i]->getHistorial(), participantes[i]->getId());
    }

    QVector<Partido *> partidos = comp->getPartidos();
    status &= this->save(partidos, comp->getId());    //guardo los partidos

    for(int i = 0; i < partidos.size(); i++){
        //guardo los resultados de cada partido
        status &= this->saveResultado(partidos[i]->getActual(), partidos[i]->getId());

        //guardo el historial de cada partido
        QVector<Resultado *> modificados = partidos[i]->getModificado();
        for(int j = 0; j < modificados.size(); j++){
            status &= this->saveResultado(modificados[j], partidos[i]->getId());
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

///esto necesita ser corregido para saber si es actual o modificado
bool GestorBaseDatos::saveResultado(Resultado *resultado, int partidoId){
    bool status = true;
    QString tabla = resultado->getTable();

    switch(tabla[0].toLatin1()){
    case 'R': //"Resultado"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        break;
    case 'P': //"Puntos"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        status &= this->save(QVector<Puntos *>(1,resultado), partidoId);
        break;
    case 'S': //"Sets"
        status &= this->save(QVector<Resultado *>(1,resultado), partidoId);
        status &= this->save(QVector<Sets *>(1,resultado), partidoId);
        break;
    }
    return status;
}


#endif // GESTORBASEDATOSSAVEESPECIALES

