/**
 * Project Pegaso
 */


#ifndef _USUARIO_H
#define _USUARIO_H

#include "Competencia.h"
#include "Lugar.h"
#include "Doc.h"
#include "Localidad.h"
#include "Auditoria.h"
#include <QVector>
#include <QString>


class Usuario {
public: 


    int getId() const;
    void setId(int value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getNombre() const;
    void setNombre(const QString &value);

    QString getApellido() const;
    void setApellido(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    int getNro_doc() const;
    void setNro_doc(int value);

    QVector<Competencia *> getCompetencias() const;
    void setCompetencias(const QVector<Competencia *> &value);

    QVector<Lugar *> getLugares() const;
    void setLugares(const QVector<Lugar *> &value);

    Doc *getDoc() const;
    void setDoc(Doc *value);

    Localidad *getLocalidad() const;
    void setLocalidad(Localidad *value);

    QVector<Auditoria *> getAuditorias() const;
    void setAuditorias(const QVector<Auditoria *> &value);

private:
    int id;
    QString password;
    QString nombre;
    QString apellido;
    QString email;
    int nro_doc;
    QVector<Competencia*> competencias;
    QVector<Lugar*> lugares;
    Doc* doc;
    Localidad* localidad;
    QVector<Auditoria*> auditorias;
};

#endif //_USUARIO_H
