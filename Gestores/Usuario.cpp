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
Provincia *Usuario::getProvincia() const
{
    return provincia;
}

void Usuario::setProvincia(Provincia *value)
{
    provincia = value;
}
Pais *Usuario::getPais() const
{
    return pais;
}

void Usuario::setPais(Pais *value)
{
    pais = value;
}
Doc *Usuario::getDoc() const
{
    return doc;
}

void Usuario::setDoc(Doc *value)
{
    doc = value;
}
QByteArray Usuario::getPassword() const
{
    return password;
}

void Usuario::setPassword(const QByteArray &value)
{
    password = value;
}
Localidad *Usuario::getLocalidad() const
{
    return localidad;
}

void Usuario::setLocalidad(Localidad *value)
{
    localidad = value;
}


QVector<Atributo> Usuario::getAtributos() const
{
    QVector<Atributo> result;

    if(id != -1){
        result.push_back(Atributo("id_usuario",QString::number(id)));
    }
    result.push_back(Atributo("email",email));
    result.push_back(Atributo("nro_doc",QString::number(nro_doc)));
    result.push_back(Atributo("id_tipo_doc", QString::number(doc->getId())));
    //result.push_back(Atributo("password",));

    return QVector<Atributo>(); //temporal
}












