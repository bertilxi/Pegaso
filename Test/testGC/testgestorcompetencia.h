#ifndef TESTGESTORCOMPETENCIA_H
#define TESTGESTORCOMPETENCIA_H


#include <QObject>
#include <QtTest>
#include "../../Gestores/GestorCompetencias.h"

class testGestorCompetencia : public QObject
{
    Q_OBJECT
public:
    testGestorCompetencia();

private Q_SLOTS:
   void crearcompetencia_liga();
   void crearcompetencia_simple();
   void crearcompetencia_sets();
   void bajacompetencia_liga_creada();
   void bajacompetencia_doble_creada();
   void bajacompetencia_liga_planificada();
   void bajacompetencia_liga_endisputa();
   void bajacompetencia_doble_finalizada();
   void modificarcompetencia_liga_creada();
   void modificarcompetencia_liga_planificada();
   void modificarcompetencia_doble_endisputa();
   void modificarcompetencia_simple_finalizada();
   void altaparticipante_liga_creada();
   void altaparticipante_liga_planificada();
   void altaparticipante_liga_endisputa();
   void altaparticipante_liga_finalizada();
   void modificarparticipante_simple_creada();
   void modificarparticipante_simple_planificada();
   void modificarparticipante_simple_endisputa();
   void eliminarparticipante_doble_creada();
   void eliminarparticipante_doble_planificada();
   void eliminarparticipante_doble_finalizada();
};
;

#endif // TESTGESTORCOMPETENCIA_H
