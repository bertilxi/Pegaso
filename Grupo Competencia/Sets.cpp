/**
 * Project Pegaso
 */


#include "Sets.h"

/**
 * Sets implementation
 */

QVector<Set> Sets::getSets() const
{
    return sets;
}

void Sets::setSets(const QVector<Set> &value)
{
    sets = value;
}
int Sets::getCant_sets() const
{
    return cant_sets;
}

void Sets::setCant_sets(int value)
{
    cant_sets = value;
}

