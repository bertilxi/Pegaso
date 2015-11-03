/**
 * Project Pegaso
 */


#include "GestorPartidos.h"

/**
 * GestorPartidos implementation
 */

void GestorPartidos::generarFixture(Competencia *comp) {
    //Llamo a la función adecuada según la modalidad de la competencia
    QString modalidad=comp->getModalidad()->getTipoMod()->getNombre();
    if(modalidad=="Liga"){
        this->generarFixtureLiga(comp);
    }
    else{
        if(modalidad=="Simple"){
            this->generarFixtureElimSimple(comp);
        }
        else
            if(modalidad=="Doble")
                this->generarFixtureElimDoble(comp);
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
        for(int j=0;j<disponibilidades.size();j++) //Compruebo en todos los lugares si tengo disponibilidad
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
    if(part->getActual()!=NULL){
        QVector<Resultado*> historial=part->getModificado();
        //Creo el nuevo resultado dependiendo el tipo de resultado
        QString tipo_resultado=comp->getModalidad()->getTipoRes()->getNombre();
        if(tipo_resultado=="Resultado"){
            Resultado *resAux=new Resultado;
            resAux->setResultadoA(part->getActual()->getResultadoA());
            resAux->setResultadoB(part->getActual()->getResultadoB());
            historial.push_back(resAux);
        }
        else if(tipo_resultado=="Puntos"){
            Puntos *resAux=new Puntos;
            resAux->setPuntosA(part->getActual()->getPuntosA());
            resAux->setPuntosB(part->getActual()->getPuntosB());
            resAux->setResultadoA(part->getActual()->getResultadoA());
            resAux->setResultadoB(part->getActual()->getResultadoB());
            historial.push_back(resAux);
        }
        else if(tipo_resultado=="Sets"){
            Sets *resAux=new Sets;
            resAux->setResultadoA(part->getActual()->getResultadoA());
            resAux->setResultadoB(part->getActual()->getResultadoB());
            resAux->setSets(part->getActual()->getSets());
            historial.push_back(resAux);
        }
        part->setModificado(historial);
        //Si es de liga hay que modificar los puntos
        if(comp->getModalidad()->getTipoMod()->getNombre()=="Liga"){
            part->getEquipoA()->getPuntaje()->restar(part->getActual(),comp->getModalidad(),"EquipoA");
            part->getEquipoB()->getPuntaje()->restar(part->getActual(),comp->getModalidad(),"EquipoB");
        }
    }
    //Seteo el nuevo resultado como actual
    part->setActual(res);
    //Si es de liga hay que modificar los puntos
   if(comp->getModalidad()->getNombre()=="Liga"){
       part->getEquipoA()->getPuntaje()->sumar(part->getActual(),comp->getModalidad(),"EquipoA");
       part->getEquipoB()->getPuntaje()->sumar(part->getActual(),comp->getModalidad(),"EquipoB");
       return;
   }
   //Si es eliminación simple o doble hay que asignar el ganador al sucesor
   Participante* ganador;
   if(comp->getModalidad()->getTipoMod()->getNombre()=="Simple"||comp->getModalidad()->getTipoMod()->getNombre()=="Doble"){
       //Obtengo el ganador
       if(res->getResultadoA()->getNombre()=="Ganó")
           ganador=part->getEquipoA();
       else ganador=part->getEquipoB();
       //Si no es el último partido lo asigno al sucesor (sucesor de ronda ganadores si es elim. doble)
       if(part->getSucesores()[0]!=NULL){
           if(part->getSucesores()[0]->getEquipoA()==NULL)
               part->getSucesores()[0]->setEquipoA(ganador);
           else part->getSucesores()[0]->setEquipoB(ganador);
       }
       if(comp->getModalidad()->getTipoMod()->getNombre()=="Simple")
           return;
   }
   //Si es eliminación doble hay que asignar el perdedor dependiendo si es ronda ganadores o perdedores, y si es el último partido hay que ver si ganó el participante de ronda perdedores para saber si hay que jugar otro partido
   Participante* perdedor;
   if(comp->getModalidad()->getTipoMod()->getNombre()=="Doble" && part->getSucesores()[1]!=NULL){
       //Obtengo el perdedor
       if(part->getEquipoA()==ganador)
           perdedor=part->getEquipoB();
       else perdedor=part->getEquipoA();
       //Lo asigno
       if(part->getSucesores()[1]->getEquipoA()==NULL)
           part->getSucesores()[1]->setEquipoA(perdedor);
       else part->getSucesores()[1]->setEquipoB(perdedor);
   }
   //Si es el último partido determino si se debe jugar uno más
   //Uso la ronda ganadores o perdedores como bandera para saber si no es un partido final en el que ya gano el equipo de ronda perdedores anteriormente
   if(part->getSucesores()[0]==NULL && part->getRonda()=="Ganadores"){
       if(ganador==part->getEquipoB()){
           //Creo un nuevo partido y lo asigno como sucesor
           Partido* nuevo=new Partido;
           nuevo->setEquipoA(part->getEquipoA());
           nuevo->setEquipoB(part->getEquipoB());
           nuevo->setFecha(part->getFecha()+1);
           QString aux="Perdedores";
           nuevo->setRonda(aux);
           nuevo->setLugar(comp->getDisponibilidades()[0]->getLugar());
           QVector<Partido*> sucesor;
           sucesor.push_back(nuevo);
           part->setSucesores(sucesor);
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
    if(comp->getModalidad()->getTipoMod()->getNombre()=="Liga")
        return true;
    else{
        int fecha=part->getFecha();
        //Me fijo si se registró un partido de la ronda posterior
        QVector<Partido*> partidos=comp->getPartidos();
        for (int i = 0; i < partidos.size(); ++i) {
            if(partidos[i]->getFecha()>fecha && partidos[i]->getActual()!=NULL){
                error="Ya se ha registrado un resultado para la siguiente ronda";
                return false;
            }
        }
        //Me fijo si no se registró un partido de la ronda anterior
        for (int i = 0; i < partidos.size(); ++i) {
            if(partidos[i]->getFecha()<fecha && partidos[i]->getActual()==NULL){
                error="No se dispone de todos los resultados para la ronda anterior";
                return false;
            }
        }
    }
    return true;
}

Res *GestorPartidos::buscarRes(QString res)
{
    for (int i = 0; i < ress.size(); ++i) {
        if(ress[i]->getNombre()==res)
            return ress[i];
    }
    return NULL;
}


void GestorPartidos::generarFixtureLiga(Competencia *comp) {

    QVector<Participante*> participantes=comp->getParticipantes();
    QVector<Partido*> partidos;
    //Algoritmo Round Robin schedule de Édouard Lucas modificado
    int n=participantes.size();
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n - i - 1 + (n&1) ; j++) { //Si son pares hago una iteración menos porque asigno especialmente al último
                Partido *part = new Partido();
                part->setEquipoA(participantes[i-1]);
                part->setEquipoB(participantes[i+j]);
                part->setFecha(((i<<1) + j - 1)%(n -1 + (n&1) )+1); //La fecha la calculo por deducción de la matriz Round Robin
                partidos.push_back(part);
            }
            //Si son pares asigno al último participante al partido que quedaría en la diagonal principal
            if(!n&1){
                Partido *part = new Partido();
                part->setEquipoA(participantes[i-1]);
                part->setEquipoB(participantes[n-1]);
                part->setFecha(((i<<1)-2)%(n-1)+1);
                partidos.push_back(part);
            }
        }
    comp->setPartidos(partidos);
}

void GestorPartidos::generarFixtureElimSimple(Competencia *comp) {
    QVector<Participante*> participantes=comp->getParticipantes();
    int n=participantes.size();
    //Si el número de participantes no es potencia de 2 hay que hacer ajustes para saber la cantidad de partido en la primera fecha
    int dif=0;
    if(!(n & (n-1))){
        dif=(n&(-n)<<1)-n; //dif es la cantidad necesaria de participantes para que n sea potencia de 2
    }

    //Asigno los participantes al primer encuentro
    QVector<Partido*> partidos;
    int i;
    //Primero hago que algunos participantes no juegen contra nadie para llegar a una cantidad de partidos potencia de 2
    for (i = 0; i < dif; ++i) {
        Partido* part=new Partido();
        part->setEquipoA(participantes[i]);
        part->setEquipoB(new Participante);//Un participante dummy
        part->setFecha(1);
        partidos.push_back(part);
    }
    //Luego asigno los demás
    for (;i < n; i+=2) {
        Partido* part=new Partido();
        part->setEquipoA(participantes[i]);
        part->setEquipoB(participantes[i+1]);
        part->setFecha(1);
        partidos.push_back(part);
    }

    //Creo el resto de los encuentros
    int fecha=2;
    //Itero sobre la cantidad necesaria de fechas y creo la cantidad necesaria de partidos en cada una
    for (int j = (n+dif)>>2 ; j >0 ; j>>=1) {//>>1 equivale a dividir por dos; empiezo en >>2 porque la primer fecha ya se asignó
        for (int k = 0; k < j; ++k) {
            Partido* part=new Partido();
            part->setFecha(fecha);
            partidos.push_back(part);
        }
        fecha++;
    }

    //Asigno los sucesores de cada encuentro
    int l=0; //l es el índice del primer partido de la fecha considerada actualmente
    for (int j = (n+dif)>>1 ; j >0 ; j>>=1){
         for (int k = 0; k < j; ++k) {
             QVector<Partido*> sucesoresAux;
             sucesoresAux.push_back(partidos[l+j+(k>>1)]);
             partidos[l+k]->setSucesores(sucesoresAux);
         }
         l+=j;
    }

    //Por cada partido auxiliar que se creó para que sea potencia de dos, declaro como ganador al participante no dummy
    for (int j = 0; j < dif; ++j) {
        Resultado *res=new Resultado; //Creo un resultado genérico porque no importan los puntos o sets
        res->setResultadoA(this->buscarRes("Ganó"));
        res->setResultadoB(this->buscarRes("Perdió"));
        partidos[i]->setActual(res);
        if(partidos[i]->getSucesores()[0]->getEquipoA()==NULL)
            partidos[i]->getSucesores()[0]->setEquipoA(partidos[i]->getEquipoA());
        else
            partidos[i]->getSucesores()[0]->setEquipoB(partidos[i]->getEquipoA());
    }
}


void GestorPartidos::generarFixtureElimDoble(Competencia *comp) {

}
