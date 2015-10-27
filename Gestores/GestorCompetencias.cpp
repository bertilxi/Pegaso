/**
 * Project Pegaso
 */


#include "GestorCompetencias.h"

/**
 * GestorCompetencias implementation
 */

Competencia *GestorCompetencias::crearCompetencia(DtoCompetencia *datos, bool operacionExitosa, QString &error)
{
    error="";
    //Valido si existe una competencia con el mismo nombre
    DtoGetCompetencia dto(datos->idUsuario,datos->nombreCompetencia,null,null,null);
    QVector<Competencia*> auxComps=gestorBaseDatos->getCompetenciasLazy(dto);
    if(! auxComps.isEmpty()){
        operacionExitosa=false;
        error="Ya existe una competencia con el mismo nombre";
        return (new Competencia);
    }

    //Creo la competencia
    Competencia *comp=new Competencia;
    comp->setEstado("Creada");
    comp->setModalidad(datos->modalidad);
    comp->setDeporte(datos->deporte);
    comp->setReglamento(datos->reglamento);
    QVector<Disponibilidad*> disponibilidades;
    for(int i=0;i<datos->lugares.size();i++){
        Disponibilidad disp = new Disponibilidad();
        disp.setDisponibilidad(datos->disponibilidades[i]);
        disp.setLugar(datos->lugares[i]);
        disponibilidades.push_back(disp);
    }
    comp->setDisponibilidades(disponibilidades);
  //  gestorBaseDatos->saveCompetencia(comp);
    operacionExitosa=true;
    error="La operación ha culminado con éxito";
    return comp;
}

void GestorCompetencias::bajaCompetencia(Competencia *comp)
{
    comp->setBorrado(true);
    comp->setFecha_y_horaB(QDateTime::currentDateTime().toString(Qt::ISODate));
    gestorBaseDatos->saveCompetencia(comp);

    //Envío un mail a los participantes de que se ha eliminado la competencia
    QString destinatarios;
    QVector<Participante*> participantes=comp->getParticipantes();
    for(int i=0;i<participantes.size();i++){
        destinatarios+=participantes[i]->getCorreo() + ";";
    }
    //llamar al modulo de email con destinatarios
}

void GestorCompetencias::modCompetencia(Competencia *comp, DtoCompetencia *datos)
{
    //Si la competencia ya comenzó su disputa solo se permite modificar el nombre y el reglamento
    if(comp->getEstado()=="Creada"||comp->getEstado()=="Planificada"){
        comp->setModalidad(datos->modalidad);
        comp->setDeporte(datos->deporte);

        //Elimino las antiguas disponibilidades para poder reemplazarlas
        QVector<Disponibilidad*> disponibilidades=comp->getDisponibilidades();
        for(int i=0;i<disponibilidades.size();i++){
            delete disponibilidades[i];
        }
        disponibilidades.clear();

        //Creo y asigno las nuevas disponibilidades
        for(int i=0;i<datos->lugares.size();i++){
            Disponibilidad disp = new Disponibilidad();
            disp.setDisponibilidad(datos->disponibilidades[i]);
            disp.setLugar(datos->lugares[i]);
            disponibilidades.push_back(disp);
        }
        comp->setDisponibilidades(disponibilidades);
    }

    comp->setNombre(datos->nombreCompetencia);
    comp->setReglamento(datos->reglamento);

    //Guardo los cambios
    gestorBaseDatos->saveCompetencia(comp);
}

bool GestorCompetencias::altaParticipante(Competencia *comp, DtoParticipante *datos, QString &error)
{
    error="";
    //Valido si existe un participante con el mismo nombre o correo
    QVector<Participante*> participantes=comp.getParticipantes();
    for(int i=0;i<participantes.size();i++){
        if(datos->correo==participantes[i]->getCorreo()){
            error+="El correo ya existe.\n";
        }
        if(datos->nombre==participantes[i]->getNombre()){
            error+="El nombre ya existe.\n";
        }
    }
    if(error!=""){
        return false;
    }

    //Creo el participante y lo asigno a la competencia
    Participante *part=new Participante;
    part->setCorreo(datos->correo);
    part->setImg(datos->imgUrl);
    part->setNombre(datos->nombre);
    participantes.push_back(part);
    comp->setParticipantes(participantes);
    error="La operación ha culminado con éxito";
    return true;
}

void GestorCompetencias::eliminarParticipante(Competencia *comp, Participante *part)
{
    //Busco el participante a eliminar y lo elimino
    QVector<Participante*> participantes=comp->getParticipantes();
    participantes.removeOne(part);
    delete part;
    comp->setParticipantes(participantes);

    //Elimino el fixture si existiera
    QVector<partidos*> partidos=comp->getPartidos();
    for(int i=0;i<partidos.size();i++){
        delete partidos[i];
    }
    partidos.clear();
    comp->setPartidos(partidos);

    //Seteo la competencia como "Creada" y la guardo
    comp->setEstado("Creada");
    gestorBaseDatos->saveCompetencia(comp);
}

bool GestorCompetencias::modParticipante(Participante *part, DtoParticipante *datos, QString &error)
{
    error="";
    //Busco si ya existe un participante con el nuevo correo o nombre
    QVector<Participante*> participantes=comp.getParticipantes();
    for(int i=0;i<participantes.size();i++){
        if(datos->correo==participantes[i]->getCorreo() && participantes[i]!=part){
            error+="El correo ya existe.\n";
        }
        if(datos->nombre==participantes[i]->getNombre() && participantes[i]!=part){
            error+="El nombre ya existe.\n";
        }
    }
    if(error!=""){
        return false;
    }

    //Creo una nueva entrada en el historial y la asigno
    HistorialParticipante *registro=new HistorialParticipante(part);
    QVector<HistorialParticipante> *historial=part->getHistorial();
    historial->push_back(registro);
    part->setHistorial(historial);

    //Modifico los datos del participante
    part->setCorreo(datos->correo);
    part->setNombre(datos->nombre);
    part->setImg(datos->imgUrl);

    //Guardo los cambios
    gestorBaseDatos->saveParticipante(part);
}
void GestorCompetencias::nuevoResultado(Competencia *comp, Partido *part, Resultado *res)
{
    gestorPartidos->nuevoResultado(comp,part,res);
}

Competencia *GestorCompetencias::getCompetenciaFull(int id_comp)
{
    return gestorBaseDatos->getCompetenciaFull(id_comp);
}

QVector<Competencia *> GestorCompetencias::getCompetenciasLazy(DtoGetCompetencia *datos)
{
    return gestorBaseDatos->getCompetenciasLazy(datos);
}

bool GestorCompetencias::generarFixture(Competencia *comp, QString error)
{
    //Elimino el fixture si existiera
    QVector<partidos*> partidos=comp->getPartidos();
    for(int i=0;i<partidos.size();i++){
        delete partidos[i];
    }
    partidos.clear();
    comp->setPartidos(partidos);

    //Llamo a gestor partidos para que genere el fixture
    gestorPartidos->generarFixture(comp);

    //Seteo la competencia como "Planificada" y la guardo
    comp->setEstado("Planificada");
    gestorBaseDatos->saveCompetencia(comp);
}

bool GestorCompetencias::puedeModificar(Partido *part, Competencia *comp, QString &error)
{
    return gestorPartidos->puedeModificar(part,comp,error);
}
