#ifndef ATRIBUTO_H
#define ATRIBUTO_H

class Atributo
{
public:
    QString campo;
    QString valor;
    Atributo() = default;
    Atributo(QString campoP, QString valorP): campo(campoP), valor(valorP) {}
};

#endif // ATRIBUTO_H

