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
};

#endif // GENERADOREXCEL_H
