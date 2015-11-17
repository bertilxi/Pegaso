#ifndef GENERADOREXCEL_H
#define GENERADOREXCEL_H

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "../../Gestores/Competencia.h"

class GeneradorExcel
{
public:
    void generarExcel(Competencia *comp);
private:
    void mod_puntuacion_con_empate(Competencia *comp,QXlsx::Document &xlsx);
    void mod_puntuacion_sin_empate(Competencia *comp,QXlsx::Document &xlsx);
    void no_puntuacion_con_empate(Competencia *comp,QXlsx::Document &xlsx);
    void no_puntuacion_sin_empate(Competencia *comp,QXlsx::Document &xlsx);
};

#endif // GENERADOREXCEL_H
