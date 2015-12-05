/**
 * Project Pegaso
 */


#include "Sets.h"

/**
 * Sets implementation
 */


QVector<Set *> Sets::getSets() const
{
    return sets;
}

void Sets::setSets(const QVector<Set *> &value)
{
    sets = value;
}

bool Sets::operator==(const Sets &other) const
{
    if(other.getSets().size()!=sets.size()){
        qDebug()<<"Cant_sets: "<<other.getSets().size()<<" "<<sets.size()<<" en resultado";
        return 0;
    }
    if(other.getResultadoA()->getNombre()!=resultadoA->getNombre()){
        qDebug()<<"ResultadoA: "<<other.getResultadoA()->getNombre()<<" "<<resultadoA->getNombre()<<" en resultado";
        return 0;
    }
    if(other.getResultadoB()->getNombre()!=resultadoB->getNombre()){
        qDebug()<<"ResultadoB: "<<other.getResultadoB()->getNombre()<<" "<<resultadoB->getNombre()<<" en resultado";
        return 0;
    }
    QVector<Set *> otherSets(other.getSets());
    if(otherSets.size()!=sets.size()){
        qDebug()<<"Por Sets";
        return 0;
    }
    for(int i=0;i<otherSets.size();i++){
        if(!(*otherSets[i] == *sets[i])){
            qDebug()<<"en Set "<<i;
            return 0;
        }
    }
    return 1;
}

QString Sets::getTable() const{
    return "Por Sets";
}

Sets::~Sets()
{
    for(int i = 0; i < sets.size(); i++){
        delete sets[i];
    }
}
