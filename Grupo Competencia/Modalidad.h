/**
 * Project Pegaso
 */


#ifndef _MODALIDAD_H
#define _MODALIDAD_H

#include <QString>

class Modalidad {
public:
    int getId() const;
    void setId(int value);

    QString getNombre() const;
    void setNombre(const QString &value);

    QString getTipo_resultado() const;
    void setTipo_resultado(const QString &value);

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

private:
    int id;
    QString nombre;
    QString tipo_resultado;
    int cant_max_sets;
    int puntos_presentarse;
    int puntos_ganar;
    bool empate;
    int puntos_empate;
};

#endif //_MODALIDAD_H
