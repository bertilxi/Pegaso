#include "gui.h"

MainWindow::MainWindow(GUI* guiP, GestorUsuarios *gestorUsuariosP, QWidget *parent):
    QMainWindow(parent), gui(guiP), gestorUsuarios(gestorUsuariosP) ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // se encripta la contraseña a penas se pide por seguridad
    QString password = ui->lineEdit_2->text();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    qDebug() << hash.result().toHex();
    QString passwordEncriptada = hash.result().toHex();
    QString email = ui->lineEdit->text();
    QVector<QString> args;
    args.append(email);
    args.append(passwordEncriptada);
    // se envian datos se pide la accion correspondiente
    gui->handleMain(this,QString("pantallaUsuario"),args);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
    qDebug()<<"se cerro el programa";
}


void GUI::handleMain(QMainWindow* a, QString b, QVector<QString> datos)
{
    if (b == "pantallaUsuario")
    {
        /*
        Usuario* u = gestorDB->loadUsuario(datos[0]});

        QString passwordDB = u.getPassword();
        */
        if(1/*datos[1] == passwordDB*/){
            pantalla_usuario * p  = new pantalla_usuario();
            a->close();
            p->show();

        }


    }
    if (b == "registrarUsuario")
    {
        /* code */
    }
    if (b == "listarTodasCompetencias")
    {
        /* code */
    }
}

void GUI::handlePantallaUsuario(QDialog *a, QString b)
{
    if (b == "listarCompetencias"){



        listar_competencias * l = new listar_competencias();
        a->close();

        l->show();

    }

    if (b == "modificarUsuario")
    {
        /* code */
    }
    if (b == "listarLugares")
    {
        /* code */
    }
}

void GUI::handleListarCompetencias(QDialog *a, QString b)
{
    if (b == "altaCompetencia")
    {
        alta_competencia * al = new alta_competencia();
        al->show();
        a->close();
    }
    if (b == "verCompetencia")
    {
        /* code */
    }
}

void GUI::handleListarLugares(QDialog *a, QString b)
{
    if (b == "altaLugar")
    {
        /* code */
    }
    if (b == "bajaLugar")
    {
        /* code */
    }
    if (b == "modificarLugar")
    {
        /* code */
    }
}

void GUI::handleAltaCompetencia(QDialog *a, QString b)
{
    if (b == "listarParticipantes")
    {
        listar_competencias * l = new listar_competencias();
        l->show();
        a->close();
    }
}

void GUI::handleListarParticipantes(QDialog *a, QString b)
{
    if (b == "altaParticipante")
    {
        /* code */
    }
    if (b == "bajaParticipante")
    {
        /* code */
    }
    if (b == "modificarParticipante")
    {
        /* code */
    }
}

void GUI::handleVerCompetencia(QDialog *a, QString b)
{
    if (b == "modificarCompetencia")
    {
        /* code */
    }
    if (b == "generarFixture")
    {
        /* code */
    }
    if (b == "bajaCompertencia")
    {
        /* code */
    }
    if (b == "mostrarFixture")
    {
        /* code */
    }
    if (b == "mostrarTablasPosiciones")
    {
        /* code */
    }
}

void GUI::handleMostrarFixture(QDialog *a, QString b)
{
    if (b == "generarFixture")
    {
        /* code */
    }
}

QVector<Competencia*> GUI::handleFiltrarCompetencias(QStringList data)
{
    QString nombreComp, deporte, estado, tipoModalidad;


    Usuario*  usuario   =   gestorUsuarios->getActual();
    nombreComp          =   data[0];
    deporte             =   data[1];
    estado              =   data[2];
    tipoModalidad       =   data[3];

    Estado* e = buscarEstado(estado);
    Deporte* d = buscarDeporte(deporte);
    TipoModalidad* tm = buscarTipoModalidad(tipoModalidad);


//    QString usuarioQuery = "select id_usuario from Usuario where nombre = " + usuario;
//    int usuarioId = gestorDB->query(usuarioQuery);

//    QString deporteQuery = "select id_deporte from Deporte where nombre = " + deporte;
//    int deporteId = gestorDB->query(deporteQuery);

//    QString tipoModalidadQuery = "select id_tipo_modalidad from Tipo_modalidad where nombre = " + tipoModalidad;
//    int tipoModalidadId = gestorDB->query(tipoModalidad);
    DtoGetCompetencia* datos = new DtoGetCompetencia(usuario,nombreComp,d,tm,e);

    return gestorCompetencias->getCompetenciasLazy(datos);



}

GUI::GUI(GestorBaseDatos *gestorDBP, GestorCompetencias *gestorCompetenciasP, GestorLugares *gestorLugaresP, GestorPartidos *gestorPartidosP, GestorUsuarios *gestorUsuariosP):
    gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP)
{
    deportes /*= gestorDB->getDeportes()*/;
    paises /*= gestorDB->getPaises()*/;
    estados /*= gestorDB->getEstados()*/;
    modalidades /*= gestorDB->getModalidades*/;

}

QVector<Deporte *> GUI::getDeportes() const
{
    return deportes;
}

void GUI::setDeportes(const QVector<Deporte *> &value)
{
    deportes = value;
}

void GUI::show()
{
    MainWindow * m = new MainWindow(this,gestorUsuarios);
    m->show();

}

//void GUI::handle(QMainWindow* a, QString b, QVector<QString> args)
//{

//    if (a == "main")
//    {
//        this->handleMain(QString b);
//    }
//    else if (a == "pantallaUsuario")
//    {
//        this->handlePantallaUsuario(QString b);
//    }
//    else if (a == "listarCompetencias")
//    {
//        this->handleListarCompetencias(QString b);
//    }
//    else if (a == "listarLugares")
//    {
//        this->handleListarLugares(QString b);
//    }
//    else if (a == "altaCompetencia")
//    {
//        this->handleAltaCompetencia(QString b);
//    }
//    else if (a == "listarParticipantes")
//    {
//        this->handleListarParticipantes(QString b);
//    }
//    else if (a == "verCompetencia")
//    {
//        this->handleVerCompetencia(QString b);
//    }
//    else if (a == "mostrarFixture")
//    {
//        this->handleMostrarFixture(QString b);
//    }
//    else if (a == "cerrar")
//    {
//        /* code */
//    }
//}
