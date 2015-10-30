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

void GUI::handleFiltrarCompetencias(DtoGetCompetencia *datos)
{
    QVector<QString> tabla;
    tabla = gestorCompetencias->listarCompetencias(datos);

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
