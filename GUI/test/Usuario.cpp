/**
 * Project Pegaso
 */


#include "Usuario.h"

/**
 * Usuario implementation
 */

int Usuario::getId() const
{
    return id;
}

void Usuario::setId(int value)
{
    id = value;
}
QString Usuario::getPassword() const
{
    return password;
}

void Usuario::setPassword(const QString &value)
{
    password = value;
}
QString Usuario::getNombre() const
{
    return nombre;
}

void Usuario::setNombre(const QString &value)
{
    nombre = value;
}
QString Usuario::getApellido() const
{
    return apellido;
}

void Usuario::setApellido(const QString &value)
{
    apellido = value;
}
QString Usuario::getEmail() const
{
    return email;
}

void Usuario::setEmail(const QString &value)
{
    email = value;
}

QVector<Competencia *> Usuario::getCompetencias() const
{
    return competencias;
}

void Usuario::setCompetencias(const QVector<Competencia *> &value)
{
    competencias = value;
}
QVector<Lugar *> Usuario::getLugares() const
{
    return lugares;
}

void Usuario::setLugares(const QVector<Lugar *> &value)
{
    lugares = value;
}
Doc *Usuario::getDoc() const
{
    return doc;
}

void Usuario::setDoc(QString value)
{
    doc->setTipo(value);
}
Localidad *Usuario::getLocalidad() const
{
    return localidad;
}

void Usuario::setLocalidad(QString value)
{
    localidad->setNombre(value);
}
QVector<Auditoria *> Usuario::getAuditorias() const
{
    return auditorias;
}

void Usuario::setAuditorias(const QVector<Auditoria *> &value)
{
    auditorias = value;
}

QString Usuario::getNro_doc() const
{
    return nro_doc;
}

void Usuario::setNro_doc(const QString &value)
{
    nro_doc = value;
}










