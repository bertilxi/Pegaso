/**
 * Project Pegaso
 */


#include "Participante.h"

/**
 * Participante implementation
 */

int Participante::getId() const
{
    return id;
}

void Participante::setId(int value)
{
    id = value;
}
QString Participante::getNombre() const
{
    return nombre;
}

void Participante::setNombre(const QString &value)
{
    nombre = value;
}
QString Participante::getCorreo() const
{
    return correo;
}

void Participante::setCorreo(const QString &value)
{
    correo = value;
}
QString Participante::getImg() const
{
    return img;
}

void Participante::setImg(const QString &value)
{
    img = value;
}
QVector<HistorialParticipante *> Participante::getHistorial() const
{
    return historial;
}

void Participante::setHistorial(const QVector<HistorialParticipante *> &value)
{
    historial = value;
}
Puntaje *Participante::getPuntaje() const
{
    return puntaje;
}

void Participante::setPuntaje(const Puntaje *value)
{
    puntaje = value;
}

bool Participante::operator==(const Participante &other) const
{
    if(other.getNombre()!=nombre){
        qDebug()<<"Nombre: "<<other.getNombre()<<" "<<nombre<<" en participante "<<id;
        return 0;
    }
    if(other.getCorreo()!=correo){
        qDebug()<<"Correo: "<<other.getCorreo()<<" "<<correo<<" en participante "<<id;
        return 0;
    }
    if(other.getImg()!=img){
        qDebug()<<"Img: "<<other.getImg()<<" "<<img<<" en participante "<<id;
        return 0;
    }
    if(!(*(other.getPuntaje()) == *puntaje)){
        qDebug()<<" en puntaje en participante "<<id;
        return 0;
    }
    QVector<HistorialParticipante *> otherHistorial(other.getHistorial());
    if(otherHistorial.size()!=Historial.size()){
        qDebug()<<"Historial en participante "<<id;
        return 0;
    }
    for(int i=0;i<otherHistorial.size();i++){
        if(!(*otherHistorial[i] == *historial[i])){
            qDebug()<<" en participante "<<id;
            return 0;
        }
    }
    return 1;
}

static bool LessThan(Participante *a, Participante *b){
    return a->getId() < b->getId();
}

QString Participante::getTable(){
    return "Participante";
}

/**
 * @brief getAtributos
 * @return una lista de los atributos de Participante con el correspondiente nombre
 * de sus columnas en la tabla Participante de la Base de Datos. Los atributos
 * retornados han sido casteados a QString's.
 */
QVector<Atributo> Participante::getAtributos() const{
    QVector<Atributo> result;
    if(id != -1){
        result.push_back(Atributo("id_participante",QString::number(id)));
    }
    result.push_back(Atributo("imagen", img);
    result.push_back(Atributo("nombre", nombre);
    result.push_back(Atributo("correo", correo);
    result.push_back(Atributo("puntos", QString::number(puntaje->getPuntos())));
    result.push_back(Atributo("pg", QString::number(puntaje->getPG())));
    result.push_back(Atributo("pp", QString::number(puntaje->getPP())));
    result.push_back(Atributo("pe", QString::number(puntaje->getPE())));
    result.push_back(Atributo("tf", QString::number(puntaje->getTF())));
    result.push_back(Atributo("tc", QString::number(puntaje->getTC())));
    result.push_back(Atributo("dif", QString::number(puntaje->getDif())));

    return result;
}




