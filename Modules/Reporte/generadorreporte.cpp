#include "generadorreporte.h"

void generadorReporte::generar(Competencia *comp) {
    //Creo el reporte

    QtRPT* report = new QtRPT();

    //Obtengo los participante para después obtener el puntaje de cada uno
    QVector<Participante*> participantes=comp->getParticipantes();

    //Seteo la cantidad de filas que tendrá el reporte
    report->recordCount << participantes.size();

    //Abro el template del reporte dependiendo la modalidad de la competencia
    QString fileName;
    if(comp->getModalidad()->getTipoRes()->getNombre().toLower()=="puntuación"){
        if(comp->getModalidad()->getEmpate()==true)
            fileName = ":/reporte.xml";
        else
            fileName = ":/reporte_sin_empate.xml";
    }
    else{
        if(comp->getModalidad()->getEmpate()==true)
            fileName = ":/reporte_no_puntuacion.xml";
        else
            fileName = ":/reporte_no_puntuacion_sin_empate.xml";
    }

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
    if (paramName == "fecha")
        paramValue = comp->getFechaActual();
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
