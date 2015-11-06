#ifndef GUI_H
#define GUI_H

#include <QVector>

#include "GestorBaseDatos.h"
#include "GestorCompetencias.h"
#include "GestorLugares.h"
#include "GestorPartidos.h"
#include "GestorUsuarios.h"

#include "alta_competencia.h"
#include "alta_competencia_eliminacion.h"
#include "alta_competencia_liga.h"
#include "alta_participante.h"

#include "listar_competencias.h"
#include "mainwindow.h"
#include "modificar_competencia.h"
#include "pantalla_usuario.h"
#include "ver_competencia.h"

#include "dtos.h"
#include <QMainWindow>
#include <QDebug>
#include "ui_mainwindow.h"
#include <QCryptographicHash>
#include <QValidator>
#include <QRegExp>
#include <QMessageBox>

#include "Pais.h"
#include "Provincia.h"
#include "Localidad.h"
#include "Doc.h"
#include "estado.h"
#include "res.h"
#include "tipomodalidad.h"
#include "tiporesultado.h"


namespace Ui {
class MainWindow;
}

class MainWindow;
class pantalla_usuario;
class listar_competencias;

class GUI
{
private:
    QWidget* ventanaActual;
    QWidget* ventanaAnterior;

    GestorBaseDatos* gestorDB;
    GestorCompetencias* gestorCompetencias;
    GestorLugares* gestorLugares;
    GestorPartidos* gestorPartidos;
    GestorUsuarios* gestorUsuarios;


    QVector<Deporte*> deportes;
    QVector<Pais*> paises;
    QVector<Estado*> estados;
//    QVector<Lugar*> lugares;
    QVector<Res*> res;
    QVector<TipoModalidad*> modalidades;
    QVector<TipoResultado*> tiposResultado;
    QVector<Provincia*> provincias;
    QVector<Localidad*> localidades;
    QVector<Doc*> documentos;

    Estado* buscarEstado(QString estado);
    Deporte* buscarDeporte(QString deporte);
    TipoModalidad* buscarTipoModalidad(QString tipoMod);


public:
    void show();
    void handleMain(QMainWindow* a, QString b, QString email, QByteArray pass);
    void handlePantallaUsuario(QDialog* a, QString b);
    void handleListarCompetencias(QDialog* a, QString b, Competencia* comp = NULL);
    void handleListarLugares(QDialog* a , QString b);
    void handleAltaCompetencia(QDialog *a, QString b, QString nombreComp, Deporte *dep, QVector<Lugar *> lugs,
                               QVector<int> disps, Modalidad *mod, QString reglamento);
    void handleListarParticipantes(QDialog* a, QString b);
    void handleVerCompetencia(QDialog* a, QString b);
    void handleMostrarFixture(QDialog* a, QString b);
    QVector<Competencia*> handleFiltrarCompetencias(QStringList datos);
    GUI(GestorBaseDatos* gestorDBP, GestorCompetencias* gestorCompetenciasP,
        GestorLugares* gestorLugaresP, GestorPartidos* gestorPartidosP, GestorUsuarios* gestorUsuariosP,
        QVector<Deporte*> deportesP, QVector<Pais*> paisesP, QVector<Estado*> estadosP, QVector<TipoModalidad*> modalidadesP
        );
    QVector<Deporte *> getDeportes() const;
    void setDeportes(const QVector<Deporte *> &value);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(GUI* guiP , QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    GUI* gui;

};

QT_BEGIN_NAMESPACE
class QRegExp;
QT_END_NAMESPACE

class EmailValidator : public QValidator
{
    Q_OBJECT
public:
    explicit EmailValidator(QObject *parent = 0);
    State validate(QString &text, int &pos) const;
    void fixup(QString &text) const;

private:
    const QRegExp m_validMailRegExp;
    const QRegExp m_intermediateMailRegExp;
};


#endif // GUI_H
