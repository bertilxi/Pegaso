/**
 * Project Pegaso
 */


#ifndef _SETS_H
#define _SETS_H

#include <QVector>
#include <QDebug>
#include "Resultado.h"
#include "Set.h"

class Sets: public Resultado {

public: 

    bool operator==(const Sets &other)const;

    QVector<Set *> getSets() const;

    void setSets(const QVector<Set *> &value);

    QString getTable() const;

private:

    QVector<Set *> sets;

};

#endif //_SETS_H
