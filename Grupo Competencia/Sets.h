/**
 * Project Pegaso
 */


#ifndef _SETS_H
#define _SETS_H

#include "Resultado.h"
#include "Set.h"

#include <QVector>


class Sets: public Resultado {
public: 

    QVector<Set> getSets() const;
    void setSets(const QVector<Set> &value);

    int getCant_sets() const;
    void setCant_sets(int value);

private:
    int cant_sets;
    QVector<Set> sets;
};

#endif //_SETS_H
