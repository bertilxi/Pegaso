/**
 * Project Pegaso
 */


#ifndef _SETS_H
#define _SETS_H

#include "Resultado.h"
#include "Set.h"

#include <QVector>
#include <QDebug>

class Sets: public Resultado {
public: 

    int getCant_sets() const;
    void setCant_sets(int value);

    bool operator==(const Sets &other)const;

    QVector<Set *> getSets() const;
    void setSets(const QVector<Set *> &value);

private:
    int cant_sets;
    QVector<Set *> sets;
};

#endif //_SETS_H
