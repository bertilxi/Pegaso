/**
 * Project Pegaso
 */
#include<QTime>

#ifndef _AUDITORIA_H
#define _AUDITORIA_H

class Auditoria {
public:

    QTime getFecha() const;
    void setFecha(const QTime &value);

    QString getPc() const;
    void setPc(const QString &value);

private:
    QTime fecha;
    QString pc;
};

#endif //_AUDITORIA_H
