/**
 * Project Pegaso
 */

#include <QVector>
#include "dtos.h"
#include "../Grupo Competencia/Competencia.h"
#include "../Grupo Competencia/Modalidad.h"
#include "../Grupo Competencia/Participante.h"
#include "../Grupo Competencia/HistorialParticipante.h"
#include "../Grupo Competencia/Lugar.h"
#include "../Grupo Competencia/Deporte.h"
#include "../Grupo Competencia/Disponibilidad.h"
#include "../Grupo Competencia/Resultado.h"
#include "../Grupo Competencia/Partido.h"
#include "../Grupo Competencia/Puntos.h"
#include "../Grupo Competencia/Set.h"
#include "../Grupo Competencia/Sets.h"

//#include "GestorBaseDatosSaveEspeciales.h"


#ifndef _GESTORBASEDATOS_H
#define _GESTORBASEDATOS_H

class GestorBaseDatos {
public: 
    

private:

    /**
     * @brief utiliza el nombre de una tabla y conjuntos columna-valor (atributos)
     * para armar un insert SQL y ejecutarlo en la BD.
     * @param tabla
     * @param atributos
     * @return id del objeto que se acaba de guardar, asignado por la BD
     */
    int armarQuery(QString tabla, const QVector<Atributo> &atributos);
};



#endif //_GESTORBASEDATOS_H
