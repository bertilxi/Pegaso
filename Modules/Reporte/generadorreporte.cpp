#include "generadorreporte.h"

void generadorReporte::generar(Competencia *comp) {
    //Creo el reporte
    QString fileName = ":/reporte.xml";
    QtRPT* report = new QtRPT();
    //Obtengo los participante para después obtener el puntaje de cada uno
    QVector<Participante*> participantes=comp->getParticipantes();
    //Seteo la cantidad de filas que tendrá el reporte
    report->recordCount << participantes.size();
    //Abro el template del reporte
    if (report->loadReport(fileName) == false) {
        qDebug()<<"Report file not found";
    }
    //Comienzo a llenar los valores
    //Se usa un functor para simplificar
    QObject::connect(report,&QtRPT::setValue,[&](const int recNo,const QString paramName,
                     QVariant &paramValue, const int reportPage){
    (void)reportPage;
    if (paramName == "nombreCompetencia")
        paramValue = comp->getNombre();
    if (paramName == "modalidad")
        paramValue = comp->getModalidad()->getTipoMod()->getNombre();
   // if (paramName == "fecha")
   //     paramValue = comp->getFechaActual;
    if (paramName == "equipo")
        paramValue = participantes[recNo]->getNombre();
    if (paramName == "puntos")
        paramValue = participantes[recNo]->getPuntaje()->getPuntos();
    if (paramName == "pg")
        paramValue = participantes[recNo]->getPuntaje()->getPG();
    if (paramName == "pe")
        paramValue = participantes[recNo]->getPuntaje()->getPE();
    if (paramName == "pp")
        paramValue = participantes[recNo]->getPuntaje()->getPP();
    if (paramName == "tf")
        paramValue = participantes[recNo]->getPuntaje()->getTF();
    if (paramName == "pc")
        paramValue = participantes[recNo]->getPuntaje()->getTC();
    if (paramName == "dif")
        paramValue = participantes[recNo]->getPuntaje()->getDif();
    });

    report->printExec(true);
}
