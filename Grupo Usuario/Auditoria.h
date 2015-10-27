/**
 * Project Pegaso
 */
#include<QTime>

#ifndef _AUDITORIA_H
#define _AUDITORIA_H

class Auditoria {
public:
	QTime getFecha();
	QString getPc();
private: 
    QTime fecha;
    QString pc;
};

#endif //_AUDITORIA_H
