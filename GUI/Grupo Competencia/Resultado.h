/**
 * Project Pegaso
 */

#ifndef _RESULTADO_H
#define _RESULTADO_H

#include <QString>
#include <QDebug>

class Resultado {
public:
    QString getResultadoA() const;
    void setResultadoA(const QString &value);

    QString getResultadoB() const;
    void setResultadoB(const QString &value);

    bool virtual operator==(const Resultado &other)const;

protected:
    int id;
    QString resultadoA;
    QString resultadoB;
};

#endif //_RESULTADO_H
