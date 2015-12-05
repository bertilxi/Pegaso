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
#include <QFile>

using namespace std;


#ifndef _GESTORBASEDATOS_H
#define _GESTORBASEDATOS_H

class Participante;

/**
 * @brief GestorBaseDatos : Clase responsable de comunicarse directamente con
 * la base de batos, para levantar objetos, persistirlos o eliminarlos de la
 * base de datos.
 */
class GestorBaseDatos {

public: 

    GestorBaseDatos();

    /**
     * @brief carga varias competencias inicializandolas parcialmente
     * @param dto dto con los filtros para buscar competencias
     * @return una lista de punteros a competencias. Si ocurre un error,
     * retorna una lista vacía.
     *
     * Solo se carga el id y nombre de la competencia, su estado, el NOMBRE
     * de su modalidad y el ID de su deporte.
     */
    QVector<Competencia *> getCompetenciasLazy(const DtoGetCompetencia *dto) const;

    /**
     * @brief getCompetenciaFull levanta de la base de datos una Competencia completa
     * con todos los objetos que la componen
     * @param id_comp es el id de la competencia
     * @return un puntero a la competencia, o NULL si ocurrió un error.
     */
    Competencia *getCompetenciaFull(int id_comp) const;
    
    /**
     * @brief saveParticipantes guarda en la base de datos los participantes que
     * que se le pasan como argumentos
     * @param participantes son los participantes a guardar
     * @param id_comp es el id de la competencia a la cual corresponden los paarticipantes
     * @return true, si se guardaron con éxito, o false, si falló
     */
    bool saveParticipantes(QVector<Participante *> participantes, int id_comp);

    /**
     * @brief guarda una lista de objetos en la base de datos
     * @param objptrs punteros a objetos
     * @param tabla nombre de la tabla de la BD donde guardar los objetos
     * @param id_externo es un puntero a un atributo correspondiente a una fk.
     * Su valor es NULL si no se la llama con tal argumento.
     * @return true si tuvo exito, false si falló.
     */
    template <class T1>
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
     * @brief Guarda una relacion n a n entre dos objetos
     * @param obj1
     * @param obj2
     * obj1 debe conocer la tabla de la relacion entre esos dos objetos
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
            return false;
        }

        return true;
    }

    /**
     * @brief persiste un objeto Competencia y todas sus partes
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


    /**
     * @brief saveResultado guarda un objeto de la clase Resultado en la base de datos
     * @param resultado es el resultado a guardar
     * @param partidoId objeto de clase Atributo que contiene el id del partido al
     * cual corresponde el resultado
     * @return true, si se guardó con éxito, o false, si falló en guardarse
     */
    bool saveResultado(Resultado *resultado, Atributo partidoId){
        bool status = true;
        if(resultado == NULL){
            return true;
        }
        qDebug()<<"El partido que si tiene resultado es"<<partidoId.valor;
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


    /**
     * @brief cargarUsuario levanta de la base de datos al usuario con la direccion de correo
     * pasada como parámetro
     * @param correo es la dirección de correo electrónico con la que se busca al usuario
     * @return un puntero al objeto Usuario, o NULL si ningún usuario tiene ese correo
     */
    Usuario* cargarUsuario(QString correo);

    /**
     * @brief saveUsuario guarda en la base de datos el usuario que se le pasa como parámetro
     * @param usuario es el usuario a guardar
     * @return true, si se guardó correctamente; false, si falló en guardarlo
     */
    bool saveUsuario(Usuario* usuario);

    /**
     * @brief getDeportes levanta todos los deportes de la base de datos
     * @return lista de deportes
     */
    QVector<Deporte*> getDeportes();

    /**
     * @brief getPaises levanta todos los países de la base de datos
     * @return lista de países
     */
    QVector<Pais*> getPaises();

    /**
     * @brief getProvincias levanta de la base de datos todas las provincias del país
     * que se le pasa como parámetro
     * @param pais es el país cuyas provincias se van a cargar
     * @return lista de provincias
     */
    QVector<Provincia*> getProvincias(Pais* pais);

    /**
     * @brief getLocalidades levanta de la base de datos todas las localidades de la
     * provincia que se le pasa como parámetro
     * @param provincia es la provincia cuyas localidades se van a cargar
     * @return lista de localidades
     */
    QVector<Localidad*> getLocalidades(Provincia* provincia);

    /**
     * @brief getEstados levanta de la base de datos todos los estados en que puede
     * encontrarse una Competencia
     * @return lista de estados
     */
    QVector<Estado*> getEstados();

    /**
     * @brief getTipoModalidades levanta de la base de datos todos los tipos de modalidades
     * posibles (Eliminación Simple, Eliminaciñon Doble, Liga)
     * @return lista de tipos de modalidad
     */
    QVector<TipoModalidad*> getTipoModalidades();

    /**
     * @brief getLugares levanta de la base de datos todos los lugares cargados por el
     * usuario que se le pasa como parámetro
     * @param user es el usuario cuyos lugares se van a cargar
     * @return lista de lugares
     */
    QVector<Lugar *> getLugares(Usuario *user);

    /**
     * @brief getTiposResultado levanta de la base de datos todos los tipos de resultado
     * (Por Puntos, Por Sets, Partido Final)
     * @return lista de tipos de resultado
     */
    QVector<TipoResultado *> getTiposResultado();

    /**
     * @brief elimina los partidos de una competencia
     * @param comp es la competencia cuyos partidos se borrarán
     * @return true si se eliminaron correctamente, false en caso contrario
     */
    bool eliminarPartidos(Competencia *comp);

private:

    QSqlDatabase db;

    /**
     * @brief armarQuerySave toma como parámentros datos sobre un objeto y la información
     * sobre cómo guardarlos en la base de datos. Usa estos elementos para persistir un objeto
     * individual en la base de datos
     * @param tabla es el nombre de la tabla donde se almacenan los datos del objeto
     * @param atributos son pares columna-valor que indican la columna de la tabla y el valor
     * que debe guardarse en ella.
     * @return el id que este objeto tiene en la base de datos, o -1 si hubo un error.
     */
    int armarQuerySave(QString tabla, const QVector<Atributo> &atributos);

    /**
     * @brief generarQueryResultado crea y retorna un string con la consulta para levantar
     * de la base de datos un objeto de tipo Resultado
     */
    QString generarQueryResultado() const;

    /**
     * @brief generarQueryPuntos crea y retorna un string con la consulta para levantar
     * de la base de datos un objeto de tipo Puntos
     */
    QString generarQueryPuntos() const;

    /**
     * @brief generarQuerySets crea y retorna un string con la consulta para levantar
     * de la base de datos un objeto de tipo Sets
     */
    QString generarQuerySets() const;

    /**
     * @brief LessThan compara el valor de los id de dos objetos de la misma clase
     * @param obj1
     * @param obj2
     * @return true, si el id del objeto obj1 tiene un valor menor que el id del objeto obj2;
     * false, en caso contrario.
     */
    template <class T4>
    static bool LessThan(T4 *obj1, T4 *obj2)
    {
        return obj1->getId() < obj2->getId();
    }
};


#endif //_GESTORBASEDATOS_H
