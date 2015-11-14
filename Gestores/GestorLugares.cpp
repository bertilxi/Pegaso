/**
 * Project Pegaso
 */


#include "GestorLugares.h"

/**
 * GestorLugares implementation
 */


/**
 * @param datos
 * @param Datos
 */
void GestorLugares::altaLugar(DtoLugar Datos) {

}

/**
 * @param lugar
 */
void GestorLugares::bajaLugar(Lugar lugar) {

}

/**
 * @param lugar
 * @param datos
 */
void GestorLugares::modLugar(Lugar lugar, DtoLugar datos) {

}

QVector<Lugar *> GestorLugares::getLugares()
{
    return gestorDB->getLugares(gestorUsuarios->getActual());
}
