#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Test

    Competencia* comp=new Competencia();
    QString nombre="Competencia";
    Estado* est=new Estado;
    est->setNombre("En disputa");
    comp->setEstado(est);
    comp->setNombre(nombre);
    TipoResultado* tipoRes=new TipoResultado();
    nombre="Sets";
    tipoRes->setNombre(nombre);
    TipoModalidad* tipoMod=new TipoModalidad();
    nombre="Liga";
    tipoMod->setNombre(nombre);
    Modalidad* mod=new Modalidad();
    mod->setTipoRes(tipoRes);
    mod->setTipoMod(tipoMod);
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

    generadorReporte *gen=new generadorReporte();
    gen->generar(comp);
}

MainWindow::~MainWindow()
{
    delete ui;
}
