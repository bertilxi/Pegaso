#ifndef DTOS
#define DTOS

#include "Deporte.h"
#include "Modalidad.h"
#include "Lugar.h"
#include "Usuario.h"
#include "tipomodalidad.h"


class DtoGetCompetencia
{
public:

    Usuario* usuario;
    QString nombreCompetencia;
    Deporte* deporte;
    TipoModalidad* tipoModalidad;
    Estado* estado;

    DtoGetCompetencia   (Usuario* usuarioP , QString nombreCompetenciaP = NULL, Deporte* deporteP = NULL,
                        TipoModalidad* tipoModalidadP = NULL, Estado* estadoP = NULL ):
                        usuario(usuarioP), nombreCompetencia(nombreCompetenciaP), deporte(deporteP),
                        tipoModalidad(tipoModalidadP), estado(estadoP) {}

};

class DtoCompetencia
{
public:

    Usuario* usuario;
    QString nombreCompetencia;
    Deporte* deporte;
    QVector<Lugar*> lugares;
    QVector<int> disponibilidades;
    Modalidad* modalidad;
    QString reglamento;

    DtoCompetencia  (Usuario* usuarioP,QString nombreCompentenciaP, Deporte* deporteP,
                    QVector<Lugar*> lugaresP, QVector<int> disponibilidadesP, Modalidad*  modalidadP, QString reglamentoP ):
                    usuario(usuarioP),nombreCompetencia(nombreCompentenciaP), deporte(deporteP),
                    lugares(lugaresP), disponibilidades(disponibilidadesP), modalidad(modalidadP), reglamento(reglamentoP) {}

};

class DtoParticipante
{
public:

    QString nombre;
    QString correo;
    QString imgUrl;

    DtoParticipante (QString nombreP, QString correoP, QString imgUrlP):
                    nombre(nombreP), correo(correoP), imgUrl(imgUrlP) {}

};

class DtoUsuario
{
public:

    QString correo;
    QString nombre;
    QString apellido;
    QString tipoDni;
    QString numeroDni;
    QString pais;
    QString provincia;
    QString localidad;
    QByteArray password;

    DtoUsuario  (QString correoP, QString nombreP, QString apellidoP, QString tipoDniP, QString numeroDniP,
                QString paisP, QString provinciaP, QString localidadP, QByteArray passwordP):
                correo(correoP), nombre(nombreP), apellido(apellidoP), tipoDni(tipoDniP), numeroDni(numeroDniP),
                pais(paisP), provincia(provinciaP), localidad(localidadP),password(passwordP) {}

};

class DtoLugar
{
public:

    QString nombre;
    QString descripcion = NULL;
    QVector<int> DeportesId;

    DtoLugar    (QString nombreP, QString descripcionP, QVector<int> DeportesIdP):
                nombre(nombreP), descripcion(descripcionP), DeportesId(DeportesIdP) {}
};

#endif // DTOS

