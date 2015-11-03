#include "gui.h"

MainWindow::MainWindow(GUI* guiP, GestorUsuarios *gestorUsuariosP, QWidget *parent):
    QMainWindow(parent), gui(guiP), gestorUsuarios(gestorUsuariosP) ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // validadores de la interfaz

    EmailValidator* emailValidator = new EmailValidator(this);
    ui->lineEdit->setValidator(emailValidator);
    QRegExp password("[a-zA-Z0-9.-]{4,200}");
    QValidator* passwordValidator = new QRegExpValidator(password,this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setValidator(passwordValidator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // se encripta la contraseña a penas se pide por seguridad
    QString password = ui->lineEdit_2->text();

    QByteArray passwordHash = QCryptographicHash::hash(QByteArray::fromStdString(password.toStdString()),QCryptographicHash::Sha256);

    password.clear();

    QString email = ui->lineEdit->text();

    // se envian datos se pide la accion correspondiente
    gui->handleMain(this,QString("pantallaUsuario"),email,passwordHash);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
    qDebug()<<"se cerro el programa";
}


void GUI::handleMain(QMainWindow* a, QString b, QString email, QByteArray pass)
{
    if (b == "pantallaUsuario")
    {
        if(/*gestorUsuarios->login() != NULL*/ 1 ){
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

void GUI::handleListarCompetencias(QDialog *a, QString b, Competencia *comp)
{
    if (b == "altaCompetencia")
    {
        alta_competencia * al = new alta_competencia();
        al->show();
        a->close();
    }
    if (b == "verCompetencia")
    {
        ver_competencia * v = new ver_competencia();
        v->show();
        a->close();
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
        listar_competencias * l = new listar_competencias(deportes,estados,tiposModalidad);
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

    Estado* e = this->buscarEstado(estado);
    Deporte* d = this->buscarDeporte(deporte);
    TipoModalidad* tm = this->buscarTipoModalidad(tipoModalidad);


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
//    deportes = /*gestorDB->getDeportes()*/ NULL;
//    paises = /*gestorDB->getPaises()*/ NULL;
//    estados = /*gestorDB->getEstados()*/ NULL;
//    modalidades = /*gestorDB->getModalidades*/ NULL;
//    tiposModalidad = NULL;


}

QVector<Deporte *> GUI::getDeportes() const
{
    return deportes;
}

void GUI::setDeportes(const QVector<Deporte *> &value)
{
    deportes = value;
}

Estado *GUI::buscarEstado(QString estado)
{

}

Deporte *GUI::buscarDeporte(QString deporte)
{

}

TipoModalidad *GUI::buscarTipoModalidad(QString tipoMod)
{

}

void GUI::show()
{
    MainWindow * m = new MainWindow(this,gestorUsuarios);
    m->show();

}

EmailValidator::EmailValidator(QObject *parent) :
    QValidator(parent),
      m_validMailRegExp("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"),
      m_intermediateMailRegExp("[a-z0-9._%+-]*@?[a-z0-9.-]*\\.?[a-z]*")
{
}

QValidator::State EmailValidator::validate(QString &text, int &pos) const
{
    Q_UNUSED(pos)

    fixup(text);

    if (m_validMailRegExp.exactMatch(text))
        return Acceptable;
    if (m_intermediateMailRegExp.exactMatch(text))
        return Intermediate;

    return Invalid;
}

void EmailValidator::fixup(QString &text) const
{
    text = text.trimmed().toLower();
}
