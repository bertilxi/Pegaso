/**
 * Project Pegaso
 */

#include <QVector>
#include "dtos.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include "Competencia.h"
#include "Puntos.h"
#include "Sets.h"
#include <algorithm>
#include "Participante.h"
#include "Deporte.h"
#include "Pais.h"
#include "Provincia.h"
#include "Localidad.h"
#include <QSqlError>

using namespace std;


#ifndef _GESTORBASEDATOS_H
#define _GESTORBASEDATOS_H

class Participante;
class GestorBaseDatos {
public: 
    

    template <class T>
    T load(T obj, int id);

    QVector<Competencia *> getCompetenciasLazy(const DtoGetCompetencia *dto) const;

    Competencia *getCompetenciaFull(int id_comp) const;
    
    //temporal hasta redefinir el save con template
    bool save(QVector<Participante *> participantes, int id_externo);

    /**
     * @brief guarda una lista de objetos
     * @param objptrs punteros a objetos
     * @param tabla nombre de la tabla de la BD donde guardar los objetos
     * @param id_externo es un puntero a un atributo correspondiente a una fk.
     * Su valor es NULL si no se la llama con tal argumento.
     * @return true si tuvo exito, false si fallo
     */    template <class T1>
    bool save(QVector<T1 *> objptrs, Atributo *id_externo = NULL){

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
     * obj1 debe conocer la tabla de la relacion
     */
    template <class T2,class T3>
    bool saveRelacion(T2 *obj1, T3 *obj2){
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
     * @brief persiste un objeto Competencia
     * @param comp la competencia a persistir
     * @param usuarioId id del usuario al que pertenece la competencia
     * @return true si tuvo exito, false si fallo
     */
    bool saveCompetencia(Competencia *comp, int usuarioId){
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
    bool saveResultado(Resultado *resultado, Atributo partidoId){
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

        return status;
}

    template <class T4>
    QVector<T4> query(T4 obj, QVector<QString> filtros);
    
    void virtual beginTransaction();
    
    void virtual commit();
    Usuario* cargarUsuario(QString correo);
    Usuario* saveUsuario(Usuario* usuario);

    QVector<Deporte*> getDeportes();
    QVector<Pais*> getPaises();
    QVector<Provincia*> getProvincias(Pais* pais);
    QVector<Localidad*> getLocalidades(Provincia* provincia);
    QVector<Estado*> getEstados();
    QVector<Modalidad*> getModalidades();
    QVector<TipoModalidad*> getTipoModalidades();

private:

    int armarQuerySave(QString tabla, const QVector<Atributo> &atributos);
    QString generarQueryResultado(QString partidoId) const;
    QString generarQueryPuntos(QString partidoId) const;
    QString generarQuerySets(QString partidoId) const;
};


#endif //_GESTORBASEDATOS_H
