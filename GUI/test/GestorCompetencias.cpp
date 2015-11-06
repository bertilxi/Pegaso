/**
 * Project Pegaso
 */


#include "GestorCompetencias.h"

/**
 * GestorCompetencias implementation
 */

void GestorCompetencias::eliminarFixture(Competencia *comp)
{
    //Elimino el fixture si existiera
    QVector<Partido*> partidos=comp->getPartidos();
    for(int i=0;i<partidos.size();i++){
        delete partidos[i];
    }
    partidos.clear();
    comp->setPartidos(partidos);
    comp->setEstado(this->obtenerEstado("Creada"));
}

Estado *GestorCompetencias::obtenerEstado(QString estado)
{
    for (int i = 0; i < estados.size(); ++i) {
        if(estado==estados[i]->getNombre())
            return estados[i];
    }
    return NULL;
}

Competencia *GestorCompetencias::crearCompetencia(DtoCompetencia *datos, bool operacionExitosa, QString &error)
{
    error="";
    //Valido si existe una competencia con el mismo nombre
    DtoGetCompetencia dto(datos->usuario,datos->nombreCompetencia,NULL,NULL,NULL);
    QVector<Competencia*> auxComps=gestorBaseDatos->getCompetenciasLazy(&dto);
    if(! auxComps.isEmpty()){
        operacionExitosa=false;
        error="Ya existe una competencia con el mismo nombre";
        return (new Competencia);
    }

    //Creo la competencia
    Competencia *comp=new Competencia;
    comp->setEstado(this->obtenerEstado("Creada"));
    comp->setModalidad(datos->modalidad);
    comp->setDeporte(datos->deporte);
    comp->setReglamento(datos->reglamento);
    QVector<Disponibilidad*> disponibilidades;
    for(int i=0;i<datos->lugares.size();i++){
        Disponibilidad * disp = new Disponibilidad();
        disp->setDisponibilidad(datos->disponibilidades[i]);
        disp->setLugar(datos->lugares[i]);
        disponibilidades.push_back(disp);
    }
    comp->setDisponibilidades(disponibilidades);

    //Guardo la nueva competencia y marco la operación como exitosa
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());
    operacionExitosa=true;
    error="La operación ha culminado con éxito";
    return comp;
}

void GestorCompetencias::bajaCompetencia(Competencia *comp)
{
    //Marco el campo borrado, la fecha y hora en la que se hizo y guardo los cambios
    comp->setBorrado(true);
    comp->setFecha_y_horaB(QDateTime::currentDateTime().toString(Qt::ISODate));
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());

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
    if(comp->getEstado()->getNombre()=="Creada"||comp->getEstado()->getNombre()=="Planificada"){
        comp->setModalidad(datos->modalidad);
        comp->setDeporte(datos->deporte);

        //Elimino el fixture si existiera
        this->eliminarFixture(comp);

        //Elimino las antiguas disponibilidades para poder reemplazarlas
        QVector<Disponibilidad*> disponibilidades=comp->getDisponibilidades();
        for(int i=0;i<disponibilidades.size();i++){
            delete disponibilidades[i];
        }
        disponibilidades.clear();

        //Creo y asigno las nuevas disponibilidades
        for(int i=0;i<datos->lugares.size();i++){
            Disponibilidad * disp = new Disponibilidad();
            disp->setDisponibilidad(datos->disponibilidades[i]);
            disp->setLugar(datos->lugares[i]);
            disponibilidades.push_back(disp);
        }
        comp->setDisponibilidades(disponibilidades);
    }

    comp->setNombre(datos->nombreCompetencia);
    comp->setReglamento(datos->reglamento);

    //Guardo los cambios
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());
}

bool GestorCompetencias::altaParticipante(Competencia *comp, DtoParticipante *datos, QString &error)
{
    error="";
    //Valido si existe un participante con el mismo nombre o correo
    QVector<Participante*> participantes=comp->getParticipantes();
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

    //Elimino el fixture si existiera
    this->eliminarFixture(comp);

    //Guardo los cambios
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());

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
    this->eliminarFixture(comp);

    //guardo los cambios
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());
}

void GestorCompetencias::modParticipante(Competencia *comp, Participante *part, DtoParticipante *datos, QString &error)
{
    error="";
    //Busco si ya existe un participante con el nuevo correo o nombre
    QVector<Participante*> participantes=comp->getParticipantes();
    for(int i=0;i<participantes.size();i++){
        if(datos->correo==participantes[i]->getCorreo() && participantes[i]!=part){
            error+="El correo ya existe.\n";
        }
        if(datos->nombre==participantes[i]->getNombre() && participantes[i]!=part){
            error+="El nombre ya existe.\n";
        }
    }
    if(error!=""){
        return;
    }

    //Creo una nueva entrada en el historial y la asigno
    HistorialParticipante *registro=new HistorialParticipante();
    registro->setCorreo(part->getCorreo());
    registro->setImagen(part->getImg());
    registro->setNombre(part->getNombre());

    QVector<HistorialParticipante*> historial=part->getHistorial();
    historial.push_back(registro);
    part->setHistorial(historial);

    //Modifico los datos del participante
    part->setCorreo(datos->correo);
    part->setNombre(datos->nombre);
    part->setImg(datos->imgUrl);

    //Guardo los cambios
    QVector<Participante *> partList;
    partList.push_back(part);
    gestorBaseDatos->save(partList,comp->getId());
}
void GestorCompetencias::nuevoResultado(Competencia *comp, Partido *part, Resultado *res)
{
    //Asigno el nuevo resultado al partido
    gestorPartidos->nuevoResultado(comp,part,res);

    //Modifico el estado según corresponda
    comp->setEstado(this->obtenerEstado("Finalizada"));
    QVector<Partido*> partidos=comp->getPartidos();
    for (int i = 0; i < partidos.size(); ++i) {
        if(partidos[i]->getActual()==NULL){
            comp->setEstado(this->obtenerEstado("En disputa"));
            break;
        }
    }

    //Guardo los cambios
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());
}

Competencia *GestorCompetencias::getCompetenciaFull(int id_comp)
{
    return gestorBaseDatos->getCompetenciaFull(id_comp);
}

QVector<Competencia *> GestorCompetencias::getCompetenciasLazy(DtoGetCompetencia *datos)
{
    return gestorBaseDatos->getCompetenciasLazy(datos);
}

void GestorCompetencias::generarFixture(Competencia *comp, QString error)
{
    //Elimino el fixture si existiera
    this->eliminarFixture(comp);

    //Llamo a gestor partidos para que genere el fixture
    gestorPartidos->generarFixture(comp);

    //Seteo la competencia como "Planificada" y la guardo
    comp->setEstado(this->obtenerEstado("Planificada"));
    gestorBaseDatos->saveCompetencia(comp,gestorUsuarios->getActual()->getId());
}

bool GestorCompetencias::puedeModificar(Partido *part, Competencia *comp, QString &error)
{
    return gestorPartidos->puedeModificar(part,comp,error);
}

QVector<TipoResultado *> GestorCompetencias::getTiposResultado()
{
    return gestorBaseDatos->getTiposResultado();
}
