#ifndef DTOS
#define DTOS



class DtoGetCompetencia
{
public:
    QString usuario;
    QString nombreCompetencia;
    Deporte * deporte;
    QString modalidad;
    QString estado;
    DtoGetCompetencia(QString usuarioP , QString nombreCompetenciaP = NULL, Deporte * deporteP = NULL, QString modalidadP = NULL, QString estadoP = NULL ):
        usuario(usuarioP), nombreCompetencia(nombreCompetenciaP), deporte(deporteP), modalidad(modalidadP), estado(estadoP) {}

};

class DtoCompetencia
{
public:
    int idUsuario;
    QString nombreCompetencia;
    Deporte * deporte;
    QVector<Lugar*> lugares;
    QVector<int> disponibilidades;
    Modalidad * modalidad;
    QString reglamento;
    DtoCompetencia(int idUsuarioP,QString nombreCompentenciaP, Deporte * deporteP, QVector<Lugar*> lugaresP, QVector<int> disponibilidadesP, Modalidad * modalidadP, QString reglamentoP ):
        idUsuario(idUsuarioP),nombreCompetencia(nombreCompetencia), deporte(deporteP), lugares(lugaresP), disponibilidades(disponibilidadesP), modalidad(modalidadP), reglamento(reglamentoP) {}

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
    DtoUsuario(QString correoP, QString nombreP, QString apellidoP, QString tipoDniP, QString numeroDniP, QString paisP, QString provinciaP, QString localidadP):
        correo(correoP), nombre(nombreP), apellido(apellidoP), tipoDni(tipoDniP), numeroDni(numeroDniP), pais(paisP), provincia(provinciaP), localidad(localidadP) {}

};

class DtoLugar
{
public:
    QString nombre;
    QString descripcion = NULL;
    QVector<Deporte*> Deportes;
    DtoLugar(QString nombreP, QString descripcionP = NULL, QVector<Deporte*> DeportesP):
        nombre(nombreP), descripcion(descripcionP), Deportes(DeportesP) {}
};

#endif // DTOS

