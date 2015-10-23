/**
 * Project Pegaso
 */

#include <QString>


#ifndef _RESULTADO_H
#define _RESULTADO_H

class Resultado {
public:
    QString getResultadoA() const;
    void setResultadoA(const QString &value);

    QString getResultadoB() const;
    void setResultadoB(const QString &value);

protected:
    int id;
    QString resultadoA;
    QString resultadoB;
};

#endif //_RESULTADO_H
