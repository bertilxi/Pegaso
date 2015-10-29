/**
 * Project Pegaso
 */


#include "GestorUsuarios.h"

/**
 * GestorUsuarios implementation
 */


/**
 * @param datos
 */

Usuario GestorUsuarios::getActual() const
{
    return actual;
}

void GestorUsuarios::setActual(const Usuario &value)
{
    actual = value;
}
void GestorUsuarios::altaUsuario(DtoUsuario datos) {
    
}

/**
 * @param usuario
 * @param datos
 */
void GestorUsuarios::modUsuario(Usuario usuario, DtoUsuario datos) {

}

/**
 * @param email
 * @param password
 * @return Usuario$
 */
Usuario GestorUsuarios::login(QString email, QString password) {
    return NULL;
}
