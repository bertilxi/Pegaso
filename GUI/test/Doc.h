/**
 * Project Pegaso
 */


#ifndef _DOC_H
#define _DOC_H

#include <QString>

class Doc {
public:

    QString getTipo() const;

    void setTipo(const QString &value);

    int getId() const;

    void setId(int value);

    Doc();

private:
    int id;
    QString tipo;
};

#endif //_DOC_H
