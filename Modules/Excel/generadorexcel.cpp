#include "generadorexcel.h"

void GeneradorExcel::generarExcel(Competencia *comp)
{
    QXlsx::Document xlsx;

    //Armo la cabecera
    //Formateo la primer fila
    QXlsx::Format format1;
    format1.setBorderStyle(QXlsx::Format::BorderThin);
    format1.setPatternBackgroundColor(QColor(192,192,192));
    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format1.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    format1.setTopBorderStyle(QXlsx::Format::BorderMedium);
    xlsx.setColumnWidth(1,20);//La primer columna es un poco más ancha

    //Escribo la primer fila
    format1.setLeftBorderStyle(QXlsx::Format::BorderMedium);//La primer celda tiene borde izquierdo Medio
    xlsx.write("A1", "Competencia:",format1);
    format1.setLeftBorderStyle(QXlsx::Format::BorderThin);
    xlsx.write("B1",comp->getNombre(),format1);
    xlsx.mergeCells("B1:E1",format1);
    xlsx.write("F1","",format1);
    xlsx.write("G1","Fecha:",format1);
    format1.setRightBorderStyle(QXlsx::Format::BorderMedium);//La última celda tiene borde derecho Medio
///xlsx.write("H1",comp->getFechaActual(),format1);
    format1.setRightBorderStyle(QXlsx::Format::BorderThin);

    //Segunda fila
    format1.setTopBorderStyle(QXlsx::Format::BorderThin);//La línea superior ya no es Media
    format1.setLeftBorderStyle(QXlsx::Format::BorderMedium);//La primer celda tiene borde izquierdo Medio
    xlsx.write("A2","Modalidad:",format1);
    format1.setLeftBorderStyle(QXlsx::Format::BorderThin);
    xlsx.write("B2",comp->getModalidad()->getTipoRes()->getNombre(),format1);
    xlsx.mergeCells("B2:E2",format1);
    xlsx.write("F2","",format1);
    xlsx.write("G2","",format1);
    format1.setRightBorderStyle(QXlsx::Format::BorderMedium);//La última celda tiene borde derecho Medio
    xlsx.write("H2","",format1);

    //Tercer fila
    QXlsx::Format format2;
    format2.setPatternBackgroundColor(QColor(224,224,224));
    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    format2.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    format2.setBottomBorderStyle(QXlsx::Format::BorderMedium);
    format2.setLeftBorderStyle(QXlsx::Format::BorderMedium);//La primer celda tiene borde izquierdo Medio
    xlsx.write("A3","Equipo",format2);
    format2.setLeftBorderStyle(QXlsx::Format::BorderThin);
    xlsx.write("B3","Puntos",format2);
    xlsx.write("C3","PG",format2);
    xlsx.write("D3","PE",format2);
    xlsx.write("E3","PP",format2);
    xlsx.write("F3","TF",format2);
    xlsx.write("G3","TC",format2);
    format2.setRightBorderStyle(QXlsx::Format::BorderMedium);//La última celda tiene borde derecho Medio
    xlsx.write("H3","DT",format2);

    //agrego la informacion de los equipos
    //Formateo
    QXlsx::Format format3;
    format3.setBorderStyle(QXlsx::Format::BorderThin);
    format3.setBorderColor(QColor(128,128,128));
    format3.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    QXlsx::Format format4;//Para la celda más a la izquierda
    format4.setBorderStyle(QXlsx::Format::BorderThin);
    format4.setBorderColor(QColor(128,128,128));
    format4.setLeftBorderColor(QColor(0,0,0));
    format4.setLeftBorderStyle(QXlsx::Format::BorderMedium);
    format4.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    QXlsx::Format format5;//Para la celda más a la derecha
    format5.setBorderStyle(QXlsx::Format::BorderThin);
    format5.setBorderColor(QColor(128,128,128));
    format5.setRightBorderColor(QColor(0,0,0));
    format5.setRightBorderStyle(QXlsx::Format::BorderMedium);
    format5.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    //Agrego los datos
    QVector<Participante*> participantes=comp->getParticipantes();
    int fila=4;
    for(int i=0;i<participantes.size();i++,fila++){
        //Si es la última fila hay que hacer borde inferior medio
        if(i==participantes.size()-1){
            format3.setBottomBorderColor(QColor(0,0,0));
            format3.setBottomBorderStyle(QXlsx::Format::BorderMedium);
            format4.setBottomBorderColor(QColor(0,0,0));
            format4.setBottomBorderStyle(QXlsx::Format::BorderMedium);
            format5.setBottomBorderColor(QColor(0,0,0));
            format5.setBottomBorderStyle(QXlsx::Format::BorderMedium);
        }

       Puntaje* puntos=participantes[i]->getPuntaje();
       xlsx.write(fila,1,participantes[i]->getNombre(),format4);
       format1.setLeftBorderStyle(QXlsx::Format::BorderNone);
       xlsx.write(fila,2,puntos->getPuntos(),format3);
       xlsx.write(fila,3,puntos->getPG(),format3);
       xlsx.write(fila,4,puntos->getPE(),format3);
       xlsx.write(fila,5,puntos->getPP(),format3);
       xlsx.write(fila,6,puntos->getTF(),format3);
       xlsx.write(fila,7,puntos->getTC(),format3);
       xlsx.write(fila,8,puntos->getDif(),format5);
    }

    //Guardo el archivo generado
    QString nombreArchivo="Tabla_Posiciones_"+comp->getNombre();
    nombreArchivo+=".xlsx";
    xlsx.saveAs(nombreArchivo);
}
