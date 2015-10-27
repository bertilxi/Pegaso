/**
 * Project Pegaso
 */


#include "GestorPartidos.h"

/**
 * GestorPartidos implementation
 */

void GestorPartidos::generarFixture(Competencia *comp) {
    //Llamo a la función adecuada según la modalidad de la competencia
    QString modalidad=comp->getModalidad()->getNombre();
    if(modalidad=="Liga"){
        this->generarFixtureLiga(comp);
    }
    else{
        if(modalidad=="Simple"){
            this->generarFixtureElimSimple(comp);
        }
        else this->generarFixtureElimDoble(comp);
    }

//Asigno lugares de realización a los partidos

    QVector<Disponibilidad*> disponibilidades=comp->getDisponibilidades();
    //Cargo el número de disponibilidades de cada lugar
    QVector<int> numeroDisponibles;
    for (int i = 0; i < disponibilidades.size(); ++i) {
        numeroDisponibles.push_back(disponibilidades[i]->getDisponibilidad());
    }
    QVector<Partido*> partidos=comp->getPartidos();
    int actual=0; //Cual es el lugar que en el que estoy parado actualmente
    bool seAsigno; //Bandera para saber si se asigno un lugar a un partido
    for (int i = 0; i < partidos.size(); ++i) {
        seAsigno=false;
        for(j=0;j<disponibilidades.size();j++) //Compruebo en todos los lugares si tengo disponibilidad
            //Voy asignando cíclicamente los lugares
            if(numeroDisponibles[(actual+j)%disponibilidades.size()]){
                partidos[i]->setLugar(disponibilidades[actual+j]->getLugar());
                actual=actual+j+1;
                break;
            }

        //Si no hay más lugares con disponibilidad, reestablezco las disponibilidades y sigo asignando
        if(!seAsigno){
            i--; //Para que se le asigne al partido que no se le pudo asignar
            actual=0; //Para que se comience de nuevo a asignar desde el lugar 0
            //Cargo el número de disponibilidades de cada lugar
            numeroDisponibles.clear();
            for (int k = 0; k < disponibilidades.size(); ++k) {
                numeroDisponibles.push_back(disponibilidades[k]->getDisponibilidad());
            }
        }
    }
}


void GestorPartidos::nuevoResultado(Competencia *comp, Partido *part, Resultado *res) {

}


bool GestorPartidos::puedeModificar(Partido *part, Competencia *comp) {
    return false;
}


void GestorPartidos::generarFixtureLiga(Competencia *comp) {

    QVector<Participantes*> participantes=comp->getParticipantes();
    QVector<Partidos*> partidos;
    //Algoritmo Round Robin schedule de Édouard Lucas modificado
    int n=participantes.size();
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n - i - 1 + n&1 ; j++) { //Si son pares hago una iteración menos porque asigno especialmente al último
                Partido *part = new Partido;
                part->setEquipoA(participantes[i-1]);
                part->setEquipoB(participantes[i+j]);
                part->setFecha(((i<<1) + j - 1)%(n -1 + n&1 )+1); //La fecha la calculo por deducción de la matriz Round Robin
                partidos.push_back(part);
            }
            //Si son pares asigno al último participante al partido que quedaría en la diagonal principal
            if(!n&1){
                Partido *part = new Partido;
                part->setEquipoA(participantes[i-1]);
                part->setEquipoB(participantes[n-1]);
                part->setFecha(((i<<1)-2)%(n-1)+1);
                partidos.push_back(part);
            }
        }
    comp->setPartidos(partidos);
}

void GestorPartidos::generarFixtureElimSimple(Competencia *comp) {

}


void GestorPartidos::generarFixtureElimDoble(Competencia *comp) {

}
