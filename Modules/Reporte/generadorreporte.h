#ifndef GENERADORREPORTE_H
#define GENERADORREPORTE_H
#include <qtrpt.h>
#include <QString>
#include <QVariant>
#include "../../Gestores/Competencia.h"
class generadorReporte
{
public:
    void generar(Competencia *comp);
};

#endif // GENERADORREPORTE_H
