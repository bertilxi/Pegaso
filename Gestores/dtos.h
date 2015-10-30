#ifndef DTOS
#define DTOS

#include "../Grupo Competencia/Deporte.h"
#include "../Grupo Competencia/Modalidad.h"


class DtoGetCompetencia
{
public:
    int usuarioId;
    QString nombreCompetencia;
    int deporteId;
    int tipoModalidadId;
    QString estado;
    DtoGetCompetencia(int usuarioIdP , QString nombreCompetenciaP = NULL, int deporteIdP = -1, int tipoModalidadIdP = -1, QString estadoP = NULL ):
        usuarioId(usuarioIdP), nombreCompetencia(nombreCompetenciaP), deporteId(deporteIdP), tipoModalidadId(tipoModalidadIdP), estado(estadoP) {}

};

class DtoCompetencia
{
public:
    int usuarioId;
    QString nombreCompetencia;
    Deporte* deporte;
    QVector<Lugar*> lugares;
    QVector<int> disponibilidades;
    Modalidad* modalidad;
    QString reglamento;
    DtoCompetencia(int usuarioIdP,QString nombreCompentenciaP, Deporte* deporteP, QVector<Lugar*> lugaresP, QVector<int> disponibilidadesP, Modalidad*  modalidadP, QString reglamentoP ):
        usuarioId(usuarioIdP),nombreCompetencia(nombreCompentenciaP), deporte(deporteP), lugares(lugaresP), disponibilidades(disponibilidadesP), modalidad(modalidadP), reglamento(reglamentoP) {}

};

class DtoParticipante
{
public:
    QString nombre;
    QString correo;
    QString imgUrl;
    DtoParticipante(QString nombreP, QString correoP, QString imgUrlP):
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
    QString password;
    DtoUsuario(QString correoP, QString nombreP, QString apellidoP, QString tipoDniP, QString numeroDniP, QString paisP, QString provinciaP, QString localidadP, QString passwordP):
        correo(correoP), nombre(nombreP), apellido(apellidoP), tipoDni(tipoDniP), numeroDni(numeroDniP), pais(paisP), provincia(provinciaP), localidad(localidadP),password(passwordP) {}

};

class DtoLugar
{
public:
    QString nombre;
    QString descripcion = NULL;
    QVector<int> DeportesId;
    DtoLugar(QString nombreP, QString descripcionP, QVector<int> DeportesIdP):
        nombre(nombreP), descripcion(descripcionP), DeportesId(DeportesIdP) {}
};

#endif // DTOS

