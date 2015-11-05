/**
 * Project Pegaso
 */


#include "GestorUsuarios.h"

/**
 * GestorUsuarios implementation
 */

Usuario *GestorUsuarios::getActual() const
{
    return actual;
}

void GestorUsuarios::setActual( Usuario *value)
{
    actual = value;
}

bool GestorUsuarios::altaUsuario(DtoUsuario *datos,QString &error) {
    error="";
    //Compruebo que no haya un usuario ya registrado con ese correo
    if(gestorDB->cargarUsuario(datos->correo)!=NULL){
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
    nuevo->setPassword(datos->password);

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
Usuario* GestorUsuarios::login(QString email, QByteArray password) {
    QString error="";
    //Obtengo el usuario con ese correo si no existe retorno NULL
    Usuario *user=gestorDB->cargarUsuario(email);
    if(user==NULL){
        return NULL;
    }

    //Comparo las contraseñas

    if(password!=user->getPassword())
        return NULL;
    else{
     //Registro el inicio de sesión
        Auditoria* aud=new Auditoria();
        aud->setFecha(QDateTime::currentDateTime().toString(Qt::ISODate));
        aud->setPc(QHostInfo::localHostName());
        QVector<Auditoria*> auditorias=user->getAuditorias();
        auditorias.push_back(aud);
        user->setAuditorias(auditorias);
        //Guardo para que quede registrado el nuevo inicio de sesión
        gestorDB->saveUsuario(user);
        //retorno el usuario cargado
        return user;
    }
}
