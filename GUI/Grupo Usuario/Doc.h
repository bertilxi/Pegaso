/**
 * Project Pegaso
 */


#ifndef _DOC_H
#define _DOC_H

class Doc {
public:

    QString getTipo() const;
    void setTipo(const QString &value);

private:
    QString tipo;
};

#endif //_DOC_H
