#ifndef DTOS
#define DTOS

#include "../Grupo Competencia/Deporte.h"
#include "../Grupo Competencia/Modalidad.h"


class DtoGetCompetencia
{
public:
    QString usuario;
    QString nombreCompetencia;
    int deporteId;
    int modalidadId;
    QString estado;
    DtoGetCompetencia(QString usuarioP , QString nombreCompetenciaP = NULL, int deporteIdP = NULL, int modalidadIdP = NULL, QString estadoP = NULL ):
        usuario(usuarioP), nombreCompetencia(nombreCompetenciaP), deporteId(deporteIdP), modalidadId(modalidadIdP), estado(estadoP) {}

};

class DtoCompetencia
{
public:
    int idUsuario;
    QString nombreCompetencia;
    int deporteId;
    QVector<Lugar*> lugares;
    QVector<int> disponibilidades;
    int modalidadId;
    QString reglamento;
    DtoCompetencia(int idUsuarioP,QString nombreCompentenciaP, int deporteIdP, QVector<Lugar*> lugaresP, QVector<int> disponibilidadesP, int  modalidadIdP, QString reglamentoP ):
        idUsuario(idUsuarioP),nombreCompetencia(nombreCompentenciaP), deporteId(deporteIdP), lugares(lugaresP), disponibilidades(disponibilidadesP), modalidadId(modalidadIdP), reglamento(reglamentoP) {}

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

