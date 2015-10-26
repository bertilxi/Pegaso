#include <QCoreApplication>
#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxformat.h"

/*
Faltan las líneas de borde
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
       QXlsx::Document xlsx;

       //armo la cabecera
       QXlsx::Format format1;
       format1.setPatternBackgroundColor(QColor(130,130,130));
       format1.setHorizontalAlignment(Format::AlignHcenter);
       format1.setVerticalAlignment(Format::AlignVcenter);
       xlsx.write("A1", "Competencia:",format1);
       xlsx.write("A2","Modalidad:",format1);
       //xlsx.write("B1",comp->GetNombre(),format1);
       xlsx.mergeCells("B1:E1",format1);
       //xlsx.write("B2",comp->GetModalidad(),format1);
       xlsx.mergeCells("B2:E2",format1);
       xlsx.write("F1","",format1);
       xlsx.write("F2","",format1);
       xlsx.write("G1","Fecha:",format1);
       xlsx.write("G2","",format1);
       //xlsx.write("H1",comp->GetFechaActual(),format1);
       xlsx.write("H2","",format1);

       //nombre de las columnas
       QXlsx::Format format2;
       format2.setPatternBackgroundColor(QColor(190,190,190));
       format2.setHorizontalAlignment(Format::AlignHcenter);
       format2.setVerticalAlignment(Format::AlignVcenter);
       xlsx.write("A3","Equipo",format2);
       xlsx.write("B3","Puntos",format2);
       xlsx.write("C3","PG",format2);
       xlsx.write("D3","PE",format2);
       xlsx.write("E3","PP",format2);
       xlsx.write("F3","TF",format2);
       xlsx.write("G3","TC",format2);
       xlsx.write("H3","DT",format2);

       //agrego la informacion de los equipos
       /*
       QXlsx::Format format3;
       QVector<Participantes*> participantes=comp.GetParticipantes();
       int fila=4;
       for(int i=0;i<participantes.size();i++,fila++){
          Puntaje* puntos=participantes[i]->GetPuntaje();
          xlsx.write("A" + QString::number(fila) ,comp->GetNombre(),format3);
          xlsx.write("B" + QString::number(fila) ,participantes->GetPuntos(),format3);
          xlsx.write("C" + QString::number(fila) ,participantes->GetPG(),format3);
          xlsx.write("D" + QString::number(fila) ,participantes->GetPE(),format3);
          xlsx.write("E" + QString::number(fila) ,participantes->GetPP(),format3);
          xlsx.write("F" + QString::number(fila) ,participantes->GetTF(),format3);
          xlsx.write("G" + QString::number(fila) ,participantes->GetTC(),format3);
          xlsx.write("H" + QString::number(fila) ,participantes->GetDT(),format3);
       }
       */
       xlsx.saveAs("Test.xlsx");
    return 0;
}
