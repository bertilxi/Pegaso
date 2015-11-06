/**
 * Project Pegaso
 */


#include "GestorLugares.h"

/**
 * GestorLugares implementation
 */

void GestorLugares::altaLugar(DtoLugar Datos) {

}

void GestorLugares::bajaLugar(Lugar lugar) {

}

void GestorLugares::modLugar(Lugar lugar, DtoLugar datos) {

}

QVector<Lugar *> GestorLugares::getLugares()
{
    return gestorDB->getLugares(gestorUsuarios->getActual());
}
