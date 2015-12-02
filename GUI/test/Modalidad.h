/**
 * Project Pegaso
 */


#ifndef _MODALIDAD_H
#define _MODALIDAD_H

#include <QString>
#include <QDebug>
#include <QVector>
#include "Atributo.h"
#include "tiporesultado.h"
#include "tipomodalidad.h"

class Modalidad {
public:
    int getId() const;

    void setId(int value);

    int getCant_max_sets() const;

    void setCant_max_sets(int value);

    int getPuntos_presentarse() const;

    void setPuntos_presentarse(int value);

    int getPuntos_ganar() const;

    void setPuntos_ganar(int value);

    bool getEmpate() const;

    void setEmpate(bool value);

    int getPuntos_empate() const;

    void setPuntos_empate(int value);

    bool operator==(const Modalidad &other)const;

    QString getTable();

    QVector<Atributo> getAtributos() const;

    int getId_nombre() const;

    void setId_nombre(int value);

    void setTipoRes(TipoResultado *value);

    TipoModalidad *getTipoMod() const;

    void setTipoMod(TipoModalidad *value);

    TipoResultado *getTipoRes() const;

    Modalidad();

    int getPuntos_no_presentarse() const;
    void setPuntos_no_presentarse(int value);

private:
    
    int id;
    
    TipoModalidad *tipoMod;
    
    TipoResultado *tipoRes;
    
    int cant_max_sets;

    int puntos_presentarse;
    
    int puntos_no_presentarse;

    int puntos_ganar;

    bool empate;

    int puntos_empate;

};

#endif //_MODALIDAD_H
