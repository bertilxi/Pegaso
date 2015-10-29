/**
 * Project Pegaso
 */


#include "GestorUsuarios.h"

/**
 * GestorUsuarios implementation
 */

Usuario GestorUsuarios::getActual() const
{
    return actual;
}

void GestorUsuarios::setActual(const Usuario &value)
{
    actual = value;
}
bool GestorUsuarios::altaUsuario(DtoUsuario *datos,QString &error) {
    error="";
    //Compruebo que no haya un usuario ya registrado con ese correo
    if(gestorDB->cargarUsuario(datos->correo)!=null){
        error="Ya existe un usuario con el mismo correo electrónico";
        return false;
    }

    //Creo el nuevo usuario
    Usuario *nuevo=new Usuario;
    nuevo->setApellido(datos->apellido);
    nuevo->setDoc(datos->tipoDni);
    nuevo->setNro_doc(datos->numeroDni);
    nuevo->setEmail(datos->correo);
    nuevo->setLocalidad(datos->localidad);
    nuevo->setNombre(datos->nombre);

    //Guardo la contraseña encriptada (uso Sha2_256, pero se podría usar otro si queremos más seguridad)
    //Deberíamos generar la sal aleatoriamente y que sea distinta para cada usuario pero implicaría cambiar las tablas para guardar cada una junto con su contraseña encriptada pero creo que no vale la pena
    QString pass=datos->password+"nl3ildgsysxsñe{ñs-e}l}af4l5{.d";
    QByteArray hash=QCryptographicHash::hash(QByteArray::fromStdString(pass.toStdString()),QCryptographicHash::Sha256);
    //Espero que no haya colisiones por pasar de QByteArray a Qstring (Qstring usa solo caracteres imprimibles)
    //Si queremos guardar directamente como QByteArray deberíamos cambiar la forma en como hacemos los querystr y no creo que merezca la pena
    pass=QString::fromStdString(hash1.toStdString());
    nuevo->setPassword(pass);

    //Guardo el nuevo usuario
    gestorDB->saveUsuario(nuevo);
    error="El usuario ha sido creado exitosamente";
    return true;
}

/**
 * @param usuario
 * @param datos
 */
void GestorUsuarios::modUsuario(Usuario *usuario, DtoUsuario *datos) {
    usuario->setNombre(datos->nombre);
    usuario->setApellido(datos->apellido);
    usuario->setDoc(datos->tipoDni);
    usuario->setNro_doc(datos->numeroDni);
    usuario->setLocalidad(datos->localidad);
    //El caso de uso no contempla la posibilidad de modificar la contraseña

    //Guardo los cambios
    gestorDB->saveUsuario(usuario);
}

/**
 * @param email
 * @param password
 * @return Usuario
 */
Usuario* GestorUsuarios::login(QString email, QString password) {
    error="";
    //Obtengo el usuario con ese correo si no existe retorno null
    Usuario *user=gestorDB->cargarUsuario(datos->correo);
    if(user==NULL){
        return NULL;
    }

    //Comparo las contraseñas
    QString pass=password+"nl3ildgsysxsñe{ñs-e}l}af4l5{.d";
    QByteArray hash=QCryptographicHash::hash(QByteArray::fromStdString(pass.toStdString()),QCryptographicHash::Sha256);
    pass=QString::fromStdString(hash1.toStdString());

    if(pass!=user->getPassword())
        return NULL;
    else
        return user;
}
