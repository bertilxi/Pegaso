#include "gui.h"

MainWindow::MainWindow(GUI* guiP, QWidget *parent):
    QMainWindow(parent), gui(guiP), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // validadores de la interfaz

    EmailValidator* emailValidator = new EmailValidator(this);
    ui->lineEdit->setValidator(emailValidator);
    QRegExp password("[a-zA-Z0-9.-]*");
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

    QByteArray passwordHash = QCryptographicHash::hash(QByteArray::fromStdString(ui->lineEdit_2->text().toStdString()),QCryptographicHash::Sha256);

    QString email = ui->lineEdit->text();

    // se envian datos se pide la accion correspondiente
    if(ui->lineEdit_2->text().size() < 4){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor coloque una contraseña de más de 6 caracteres");
        msg->setModal(true);
        msg->exec();
    }
    else{
        gui->handleMain(this,QString("pantallaUsuario"),email,passwordHash);
    }
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
//        if(gestorUsuarios->login(email,pass) != NULL){
        if(1){
            pantalla_usuario* p = new pantalla_usuario(a);
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
        listar_competencias* l = new listar_competencias(a);
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
        alta_competencia * al = new alta_competencia(a);
        al->setModal(true);
        al->show();


    }
    if (b == "verCompetencia")
    {
//        ver_competencia * v = new ver_competencia(comp,a);
        ver_competencia * v = new ver_competencia(a);
        v->setModal(true);
        v->show();
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

void GUI::handleAltaCompetencia(QDialog *a, QString b,QStringList data)
{
    if (b == "crearCompetencia")
    {
        listar_competencias * l = new listar_competencias(a);
        a->close();
        l->show();
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

    DtoGetCompetencia* datos = new DtoGetCompetencia(usuario,nombreComp,d,tm,e);

    return gestorCompetencias->getCompetenciasLazy(datos);

}

GUI::GUI(GestorBaseDatos *gestorDBP, GestorCompetencias *gestorCompetenciasP, GestorLugares *gestorLugaresP, GestorPartidos *gestorPartidosP, GestorUsuarios *gestorUsuariosP):
    gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP), gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP)
{

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
    for (int i = 0; i < estados.size(); ++i) {
        if(estado == estados[i]->getNombre())
            return estados[i];
    }
    return NULL;
}

Deporte *GUI::buscarDeporte(QString deporte)
{
    for (int i = 0; i < deportes.size(); ++i) {
        if(deporte==deportes[i]->getNombre())
            return deportes[i];
    }
    return NULL;
}

TipoModalidad *GUI::buscarTipoModalidad(QString tipoMod)
{
    for (int i = 0; i < tiposModalidad.size(); ++i) {
        if(tipoMod==tiposModalidad[i]->getNombre())
            return tiposModalidad[i];
    }
    return NULL;
}

void GUI::show()
{
    MainWindow * m = new MainWindow(this);
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
