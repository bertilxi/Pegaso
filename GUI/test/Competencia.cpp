/**
 * Project Pegaso
 */


#include "Competencia.h"

/**
 * Competencia implementation
 */


int Competencia::getId() const
{
    return id;
}

void Competencia::setId(int value)
{
    id = value;
}

QString Competencia::getNombre() const
{
    return nombre;
}

void Competencia::setNombre(const QString &value)
{
    nombre = value;
}
QVector<Disponibilidad *> Competencia::getDisponibilidades() const
{
    return disponibilidades;
}

void Competencia::setDisponibilidades(const QVector<Disponibilidad *> &value)
{
    disponibilidades = value;
}
QVector<Participante *> Competencia::getParticipantes() const
{
    return participantes;
}

void Competencia::setParticipantes(const QVector<Participante *> &value)
{
    participantes = value;
}
Modalidad *Competencia::getModalidad() const
{
    return modalidad;
}

void Competencia::setModalidad(Modalidad *value)
{
    modalidad = value;
}
QVector<Partido *> Competencia::getPartidos() const
{
    return partidos;
}

void Competencia::setPartidos(const QVector<Partido *> &value)
{
    partidos = value;
}
Deporte *Competencia::getDeporte() const
{
    return deporte;
}

void Competencia::setDeporte(Deporte *value)
{
    deporte = value;
}

bool Competencia::operator==( Competencia &other)
{
    QVector<Disponibilidad *> otherDisponibilidades(other.getDisponibilidades());
    if(otherDisponibilidades.size()!=disponibilidades.size()){
        qDebug()<<"Disponibilidades en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherDisponibilidades.size();i++){
        if(!(*otherDisponibilidades[i] == *disponibilidades[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }

    QVector<Participante *> otherParticipantes(other.getParticipantes());
    if(otherParticipantes.size()!=participantes.size()){
        qDebug()<<" Participantes en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherParticipantes.size();i++){
        if(!(*otherParticipantes[i] == *participantes[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }

    QVector<Partido *> otherPartidos(other.getPartidos());
    if(otherPartidos.size()!=partidos.size()){
        qDebug()<<"Partidos en competencia "<<id;
        return 0;
    }
    for(int i=0;i<otherPartidos.size();i++){
        if(!(*otherPartidos[i] == *partidos[i])){
            qDebug()<<" en competencia "<<id;
            return 0;
        }
    }
    if(!(*(other.getDeporte()) == *deporte)){
        qDebug()<<" en competencia"<<id;
        return 0;
    }
    if(!(*(other.getModalidad()) == *modalidad)){
        qDebug()<<" en competencia"<<id;
        return 0;
    }
    if(other.getEstado()->getNombre()!=estado->getNombre()){
        qDebug()<<"Estado: "<<other.getEstado()->getNombre()<<" "<<estado->getNombre()<<" en competencia"<<id;
        return 0;
    }
    return 1;
}
QString Competencia::getFecha_y_horaB() const
{
    return fecha_y_horaB;
}

void Competencia::setFecha_y_horaB(const QString &value)
{
    fecha_y_horaB = value;
}
bool Competencia::getBorrado() const
{
    return borrado;
}

void Competencia::setBorrado(bool value)
{
    borrado = value;
}

QString Competencia::getReglamento() const
{
    return reglamento;
}

void Competencia::setReglamento(const QString &value)
{
    reglamento = value;
}

QString Competencia::getTable(){
    return "Competencia";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Competencia con el correspondiente nombre
 * de sus columnas en la tabla Competencia de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Competencia::getAtributos() const{
    QVector<Atributo> result;
    if(id != -1){
        result.push_back(Atributo("id_competencia",QString::number(id)));
    }
    result.push_back(Atributo("nombre",nombre));
    result.push_back(Atributo("fecha_y_horaB", fecha_y_horaB));
    result.push_back(Atributo("reglamento", reglamento));
    result.push_back(Atributo("borrado", QString::number((int)borrado)));
    result.push_back(Atributo("id_estado", QString::number(estado->getId())));
    result.push_back(Atributo("id_modalidad", QString::number(modalidad->getId())));
    result.push_back(Atributo("id_deporte", QString::number(deporte->getId())));

    return result;
}

Estado *Competencia::getEstado()
{
    return estado;
}

void Competencia::setEstado(Estado *value)
{
    estado = value;
}

void Competencia::getProximosEncuentros()
{
    QVector<Partido *> prox;

    // recorro todo los partidos de la competencia
    for (int i = 0; i < partidos.size(); ++i) {
        int fechaAux = partidos[i]->getFecha();
        // si el la fecha es mayor o igual a la fecha actual
        if( fechaAux >= fechaActual){
            // si el partido no tiene resultado tambien se mostrara como proximo
            if(partidos[i]->getActual()->getResultadoA() == NULL && partidos[i]->getActual()->getResultadoA() == NULL ){
                prox.append(partidos[i]);
            }
        }
    }
    Partido* pAux;
    for (int i = 0; i < prox.size(); ++i) {

        while(prox[i+1] != NULL && prox[i]->getFecha() > prox[i+1]->getFecha()){
            pAux = prox[i];
            prox[i] = prox[i+1];
            prox[i+1] = pAux;

        }

    }
}

int Competencia::getFechaActual()
{
    // Si la competencia no esta finalizada
    if(this->getEstado()->getNombre().toLower() != "finalizada"){

        // si no esta cargada la fecha se busca
        if(fechaActual < 0){
            int fechaAct = INT_MAX;
            int fechaAux;

            //recoremos todos los partidos
            for (int i = 0; i < partidos.size(); ++i) {
                // si algun partido no tiene el resultado cargado se ve que fecha tiene
                if(partidos[i]->getActual()->getResultadoA() == NULL || partidos[i]->getActual()->getResultadoB() == NULL){
                    fechaAux = partidos[i]->getFecha();
                    // si la fecha que tiene ese partido es menor que la fecha que suponemos actual, nos quedamos con la menor
                    if(fechaAux < fechaAct){
                        fechaAct = fechaAux;
                    }
                }
            }
            // guardamos en competencia
            fechaActual = fechaAct;
        }
        // si esta la fecha la retorna
        else {
            return fechaActual;

        }
    }
    // si la competencia esta finalizada
    else{

        // buscamos la fecha ultima y la seteamos como actual
        int maxFecha = -1;
        for (int i = 0; i < partidos.size(); ++i) {
            int fechaAux = partidos[i]->getFecha();
               if( fechaAux > maxFecha){
                   maxFecha = fechaAux;
               }
        }
        fechaActual = maxFecha;
    }
}
