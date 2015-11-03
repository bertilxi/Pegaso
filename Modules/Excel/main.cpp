#include "generadorexcel.h"
int main(int argc, char *argv[])
{
    //Test

    Competencia* comp=new Competencia();
    QString nombre="Competencia";
    comp->setNombre(nombre);
    TipoResultado* tipo=new TipoResultado();
    nombre="Liga";
    tipo->setNombre(nombre);
    Modalidad* mod=new Modalidad();
    mod->setTipoRes(tipo);
    comp->setModalidad(mod);

    Puntaje* punt=new Puntaje();
    punt->setPuntos(4);
    punt->setPG(4);
    punt->setPP(0);
    punt->setPE(0);
    punt->setTF(4);
    punt->setTC(0);
    punt->setDif(0);

    Participante *part=new Participante();
    part->setNombre("Equipo1");
    part->setPuntaje(punt);

    Puntaje* punt2=new Puntaje();
    punt2->setPuntos(3);
    punt2->setPG(3);
    punt2->setPP(1);
    punt2->setPE(0);
    punt2->setTF(3);
    punt2->setTC(1);
    punt2->setDif(2);

    Participante *part2=new Participante();
    part2->setNombre("Equipo2");
    part2->setPuntaje(punt2);

    QVector<Participante*> participantes;
    participantes.push_back(part);
    participantes.push_back(part2);
    comp->setParticipantes(participantes);

    GeneradorExcel* gen=new GeneradorExcel();
    gen->generarExcel(comp);
    delete gen;
}
