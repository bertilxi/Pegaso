/**
 * Project Pegaso
 */


#include "GestorCompetencias.h"

/**
 * GestorCompetencias implementation
 */


Competencia *GestorCompetencias::crearCompetencia(DtoCompetencia *datos, bool operacionExitosa, QString error)
{
    //Valido si existe una competencia con el mismo nombre
    /*
    DtoGetCompetencia dto(datos->idUsuario,datos->nombreCompetencia,null,null,null);
    QVector<Competencia*> auxComps=gestorBaseDatos->getCompetenciasLazy(dto);
    if(! auxComps.isEmpty()){
        operacionExitosa=false;
        error="Ya existe una competencia con el mismo nombre";
        return (new Competencia);
    }
    */
    //Creo la competencia
    Competencia *comp=new Competencia;
    comp->setEstado("Creada");
    comp->setModalidad(datos->modalidad);
    comp->setDeporte(datos->deporte);
    QVector<Disponibilidad*> disponibilidades;
    for(int i=0;i<datos->lugares.size();i++){
        Disponibilidad disp=new Disponibilidad;
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
  //  gestorBaseDatos->saveCompetencia(comp);
}

bool GestorCompetencias::modCompetencia(Competencia *comp, DtoCompetencia *datos, QString error)
{

}

bool GestorCompetencias::altaParticipante(Competencia *comp, DtoParticipante *datos, QString error)
{

}

bool GestorCompetencias::eliminarParticipante(Competencia *comp, Participante *part, QString error)
{

}

bool GestorCompetencias::modParticipante(Participante *part, DtoParticipante *datos, QString error)
{

}

void GestorCompetencias::nuevoResultado(Competencia *comp, Partido *part, Resultado *res)
{

}

Competencia *GestorCompetencias::getCompetenciaFull(int id_comp)
{

}

QVector<Competencia *> GestorCompetencias::getCompetenciasLazy(DtoGetCompetencia)
{

}

bool GestorCompetencias::generarFixture(Competencia *comp, QString error)
{

}

bool GestorCompetencias::puedeModificar(Partido *part, Competencia *comp, QString error)
{

}
