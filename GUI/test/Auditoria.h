/**
 * Project Pegaso
 */
#ifndef _AUDITORIA_H
#define _AUDITORIA_H

#include <QString>

class Auditoria {
public:

    QString getPc() const;

    void setPc(const QString &value);


    QString getFecha() const;

    void setFecha(const QString &value);

private:

    QString fecha;

    QString pc;
};

#endif //_AUDITORIA_H
