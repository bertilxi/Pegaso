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

    //Si ya tiene un resultado hay que agregarlo al historial
    if(part->getActual()!=null){
        QVector<Partido*> historial=part->getModificado();
        historial.push_back(new Partido(part->getActual()));
        part->setModificado(historial);
        //Si es de liga hay que modificar los puntos
        if(comp->getModalidad()->getNombre()=="Liga"){
            part->getEquipoA()->getPuntaje()->restar(part->getActual());
            part->getEquipoB()->getPuntaje()->restar(part->getActual());
        }
    }
    part->setActual(res);
    //Si es de liga hay que modificar los puntos
   if(comp->getModalidad()->getNombre()=="Liga"){
       part->getEquipoA()->getPuntaje()->sumar(part->getActual());
       part->getEquipoB()->getPuntaje()->sumar(part->getActual());
       return;
   }
   //Si es eliminación simple o doble hay que asignar el ganador al sucesor
   Participante* ganador;
   if(comp->getModalidad()->getNombre()=="Simple"||comp->getModalidad()->getNombre()=="Doble"){
       //Obtengo el ganador
       if(res->getResultadoA()=="Ganó")
           ganador=part->getEquipoA();
       else ganador=part->getEquipoB();
       //Si no es el último partido lo asigno al sucesor (sucesor de ronda ganadores si es elim. doble)
       if(part->getSucesores()[0]!=null){
           if(part->getSucesores()[0]->getEquipoA()==null)
               part->getSucesores()[0]->setEquipoA(ganador);
           else part->getSucesores()[0]->setEquipoB(ganador);
       }
       if(comp->getModalidad()->getNombre()=="Simple")
           return;
   }
   //Si es eliminación doble hay que asignar el perdedor dependiendo si es ronda ganadores o perdedores, y si es el último partido hay que ver si ganó el participante de ronda perdedores para saber si hay que jugar otro partido
   Participante* perdedor;
   if(comp->getModalidad()->getNombre()=="Doble" && part->sucesores[1]!=null){
       //Obtengo el perdedor
       if(part->getEquipoA()==ganador)
           perdedor=part->getEquipoB();
       else perdedor=part->getEquipoA();
       //Lo asigno
       if(part->getSucesores()[1]->getEquipoA()==null)
           part->getSucesores()[1]->setEquipoA(perdedor);
       else part->getSucesores()[1]->setEquipoB(perdedor);
   }
   //Si es el último partido determino si se debe jugar uno más
   //Uso la ronda ganadores o perdedores como bandera para saber si no es un partido final en el que ya gano el equipo de ronda perdedores anteriormente
   if(part->getSucesores()[0]==null && part->getRonda()=="Ganadores"){
       if(ganador==part->getEquipoB()){
           //Creo un nuevo partido y lo asigno como sucesor
           Partido* nuevo=new Partido;
           nuevo->setEquipoA(part->getEquipoA());
           nuevo->setEquipoB(part->getEquipoB());
           nuevo->setFecha(part->getFecha()+1);
           nuevo->setRonda("Perdedores");
           nuevo->setLugar(comp->getDisponibilidades()[0]->getLugar());
           QVector<Partido*> sucesor;
           sucesor.push_back(nuevo);
           part->setSucesor(sucesor);
           //También tengo que agregarlo a los partidos de la competencia
           QVector<Partido*> partidos=comp->getPartidos();
           partidos.push_back(nuevo);
           comp->setPartidos(partidos);
       }
   }
}
bool GestorPartidos::puedeModificar(Partido *part, Competencia *comp,QString &error) {
    error="";
    //Si la modalidad es de liga siempre se puede mofificar un resultado
    if(comp->getModalidad()->getNombre()=="Liga")
        return true;
    else{
        int fecha=part->getFecha();
        //Me fijo si se registró un partido de la ronda posterior
        QVector<Partido*> partidos=comp->getPartidos();
        for (int i = 0; i < partidos.size(); ++i) {
            if(partidos[i]->getFecha()>fecha && partidos[i]->getActual()!=null){
                error="Ya se ha registrado un resultado para la siguiente ronda";
                return false;
            }
        }
        //Me fijo si no se registró un partido de la ronda anterior
        for (int i = 0; i < partidos.size(); ++i) {
            if(partidos[i]->getFecha()<fecha && partidos[i]->getActual()==null){
                error="No se dispone de todos los resultados para la ronda anterior";
                return false;
            }
        }
    }
    return true;
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
