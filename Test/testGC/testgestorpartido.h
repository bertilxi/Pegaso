#ifndef TESTGESTORPARTIDO_H
#define TESTGESTORPARTIDO_H

#include <QObject>
#include <QtTest>
#include "../../Gestores/GestorPartidos.h"

class testGestorPartido : public QObject
{
    Q_OBJECT
public:
    testGestorPartido();

private Q_SLOTS:
    void puedemodificar_liga();
    void puedemodificar_simple();
    void puedemodificar_doble();
    void puedemodificar_simple_rondaposterior_cargada();
    void puedemodificar_simple_rondaanterior_nocargada();
    void puedemodificar_doble_rondaposterior_cargada();
    void puedemodificar_doble_rondaposterior_nocargada();
    void generarfixture_liga_10participantes();
    void generarfixture_liga_11participantes();
    void generarfixture_simple_8participantes();
    void generarfixture_simple_9participantes();
    void generarfixture_doble_8participantes();
    void generarfixture_doble_9participantes();
    void generarfixture_liga_1participante();
    void nuevoresultado_puntos();
    void nuevoresultado_resfinal();
    void nuevoresultado_sets();
};

#endif // TESTGESTORPARTIDO_H
