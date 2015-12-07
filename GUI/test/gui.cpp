#include "gui.h"
/**
 * @brief MainWindow::MainWindow : ventana principal para logearse, registrarse y ver competencias
 *
 * @param guiP : objeto gui que hace de mediador y sirve para pasar el control
 * una vez que se quiera ir a otra ventana
 *
 * @param parent : objeto tipo ventana padre que sirve como retorno, asi lo
 * implementa Qt
 */
MainWindow::MainWindow(GUI* guiP, QWidget *parent):
    QMainWindow(parent), gui(guiP), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/images/Heros128.png");
    ui->label_logo->setPixmap(pix);

    this->setWindowTitle("Sistema deportivo Pegaso");


    // validador del email
    EmailValidator* emailValidator = new EmailValidator(this);
    ui->lineEdit->setValidator(emailValidator);

    // validador de la contraseña
    QRegExp password("[a-zA-Z0-9.-]*");
    QValidator* passwordValidator = new QRegExpValidator(password,this);
    ui->lineEdit_2->setValidator(passwordValidator);


    // contraseña seteada para que no se vea al escribir
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pushButton_3->hide();
    ui->pushButton->hide();
//    this->setGeometry(0,0,350,100);

}
/**
 * @brief GUI::GUI : Mediador que controla interacion de interfaz grafica
 * y gestores de la capa logica.
 *
 * @param gestorDBP
 * @param gestorCompetenciasP
 * @param gestorLugaresP
 * @param gestorPartidosP
 * @param gestorUsuariosP
 * @param deportesP
 * @param paisesP
 * @param estadosP
 * @param modalidadesP
 *
 */
GUI::GUI(GestorBaseDatos *gestorDBP, GestorCompetencias *gestorCompetenciasP, GestorLugares *gestorLugaresP,
         GestorPartidos *gestorPartidosP, GestorUsuarios *gestorUsuariosP, QVector<Deporte *> deportesP,
         QVector<Pais *> paisesP, QVector<Estado *> estadosP, QVector<TipoModalidad *> modalidadesP):
    gestorDB(gestorDBP), gestorCompetencias(gestorCompetenciasP), gestorLugares(gestorLugaresP),
    gestorPartidos(gestorPartidosP), gestorUsuarios(gestorUsuariosP), deportes(deportesP),
    paises(paisesP), estados(estadosP), modalidades(modalidadesP)
{}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_pushButton_2_clicked
 * @details boton de login extrae toda la informacion de la ui, la verifica
 * y la envia al gestor correspondiente para luego efectuar el cambio de ventana o no
 */
void MainWindow::on_pushButton_2_clicked()
{
    // La contraseña no puede ser menor a 6 caracteres
    // si no se cumple directamente no se verifica
    // no se avisa nada al respecto
    if(ui->lineEdit_2->text().size() > 0 && ui->lineEdit->text().size() > 0 && ui->lineEdit->hasAcceptableInput() ){
        // se encripta la contraseña a penas se pide por seguridad
        QByteArray passwordHash = QCryptographicHash::hash(QByteArray::fromStdString(ui->lineEdit_2->text().toStdString()),QCryptographicHash::Sha256);

        // obtenemos el mail de la ui
        QString email = ui->lineEdit->text();

        gui->handleMain(this,QString("pantallaUsuario"),email,passwordHash);
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Complete correctamente los campos por favor");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }
}

/**
 * @brief MainWindow::on_pushButton_4_clicked
 * @details boton de cierre de la ventana principal
 */
void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}

/**
 * @brief GUI::handleMain:
 *      Handle para manejar los posibles eventos de la ventana principal
 * @param a : ventana padre a la posible ventana a instaciar
 * @param b : opcion para el handle
 * @param email : email para pedir el usuario
 * @param pass : contraseña encriptada para loggear usuario
 */
void GUI::handleMain(QMainWindow* a, QString b, QString email, QByteArray pass)
{
    if (b == "pantallaUsuario")
    {
        if(gestorUsuarios->login(email,pass) != NULL){

            pantalla_usuario* p = new pantalla_usuario(this,a);
            a->close();
            p->show();
        }
        else{
            // mensaje de error
            QMessageBox* msg = new QMessageBox(a);
            msg->setText("Nombre o contraseña incorrecta");
            QPixmap icono(":/images/Heros-rojo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }

    }
    else if (b == "registrarUsuario")
    {

        registrar_usuario * ru = new registrar_usuario(this,paises,a);
        ru->setModal(true);
        ru->show();
    }

}

void GUI::handlePantallaUsuario(QDialog *a, QString b)
{
    if (b == "listarCompetencias"){

        listar_competencias* l = new listar_competencias(this,deportes,estados,modalidades,a);
        a->close();
        l->show();
    }
    else if(b == "cerrar")
    {
           MainWindow * m = new MainWindow(this);
           m->show();
           a->close();
    }
}

void GUI::handleListarCompetencias(QDialog *a, QString b, Competencia *comp)
{
    if (b == "altaCompetencia")
    {
        Usuario* user = gestorUsuarios->getActual();

        QVector<Lugar*> lugares = gestorLugares->getLugares();

        QVector<TipoResultado*> resultados = gestorCompetencias->getTiposResultado();
        alta_competencia * al = new alta_competencia(this,deportes,lugares,modalidades, resultados, a);
        al->setModal(true);
        al->show();

    }
    else if (b == "verCompetencia")
    {
        Competencia * c = gestorCompetencias->getCompetenciaFull(comp->getId());
        ver_competencia * v = new ver_competencia(this,c,a);
        v->setModal(true);
        v->show();
    }
    else if(b == "cerrar")
    {
            pantalla_usuario* p = new pantalla_usuario(this);
            p->show();
            a->close();
    }
}

void GUI::handleAltaCompetencia(QDialog *a, QString b, QString nombreComp, Deporte* dep,
                                QVector<Lugar *> lugs, QVector<int> disps, Modalidad* mod,
                                QString reglamento)
{
    if (b == "crearCompetencia")
    {
        bool op;
        QString error;
        Usuario* user = gestorUsuarios->getActual();

        DtoCompetencia* dtoC = new DtoCompetencia(user,nombreComp,dep,lugs,disps,mod,reglamento);
        if(gestorCompetencias->crearCompetencia(dtoC,op,error) != NULL){

            QMessageBox* msg = new QMessageBox(a);
            msg->setText("Competencia creada correctamente");
            QPixmap icono(":/images/Heros-verde-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        else{
            // QMessageBox fracaso
            QMessageBox* msg = new QMessageBox(a);
            QString error1 = "Error al crear la competencia. \n" + error;
            msg->setText(error1);
            QPixmap icono(":/images/Heros-rojo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }
        a->close();

    }
}

bool GUI::handleVerCompetencia(QDialog *a, QString b, QString &error, Competencia* comp)
{
    competenciaActual = comp;
    if (b == "modificarCompetencia")
    {
        /* code */
    }
    else if (b == "generarFixture")
    {
        bool retorno = gestorCompetencias->generarFixture(comp,error);
        competenciaActual = comp;
        return retorno;
    }
    else if (b == "bajaCompetencia")
    {
        /* code */
    }
    else if (b == "mostrarFixture")
    {
        //comp = gestorCompetencias->getCompetenciaFull(comp->getId());
        //competenciaActual = comp;
        mostrar_fixture* mf = new mostrar_fixture(this,comp,a);
        mf->setModal(true);
        mf->show();
    }
    else if (b == "mostrarTablasPosiciones")
    {
        GeneradorExcel* genExcel = new GeneradorExcel();
        tabla_posiciones* t = new tabla_posiciones(this,comp,a,genExcel);
        t->setModal(true);
        t->show();
    }
    else if (b == "listarParticipantes"){

        participantes = comp->getParticipantes();
        listar_participante * lp = new listar_participante(this,comp, a);
        lp->setModal(true);
        lp->show();
    }
    return false;
}

bool GUI::handleMostrarFixture(mostrar_fixture *a, QString b,Partido* partido)
{
    if (b == "gestionarFixture")
    {
        gestionar_fixture* gf = new gestionar_fixture(competenciaActual,a,partido,this,a);
        gf->setModal(true);
        gf->show();
        return true;
    }
}

void GUI::handleGestionarFixture(QDialog *a, QString b, mostrar_fixture* mf, Partido *partP, Resultado *resP)
{
    gestorCompetencias->nuevoResultado(competenciaActual,partP,resP);

    //competenciaActual = gestorCompetencias->getCompetenciaFull(competenciaActual->getId());

    QMessageBox* msg = new QMessageBox(a);
    msg->setText("Partido cargado correctamente");
    QPixmap icono(":/images/Heros-verde-64.png");
    msg->setIconPixmap(icono);
    msg->setModal(true);
    msg->exec();
    a->close();

    mf->actualizarTabla();
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

QString GUI::handleRegistrarUsuario(DtoUsuario *datos)
{
    QString error;
    gestorUsuarios->altaUsuario(datos,error);
    return error;
}


QVector<Deporte *> GUI::getDeportes() const
{
    return deportes;
}

void GUI::setDeportes(const QVector<Deporte *> &value)
{
    deportes = value;
}

QVector<Provincia *> GUI::getProvincias(Pais *paisP)
{
    return gestorUsuarios->getProvincias(paisP);
}

QVector<Localidad *> GUI::getLocalidades(Provincia *provinciaP)
{
    return gestorUsuarios->getLocalidades(provinciaP);
}

QVector<Participante*> GUI::handleAltaParticipante(QDialog *a, QString nombre, QString email, QString ImgUrl)
{
    DtoParticipante* datos = new DtoParticipante(nombre,email,ImgUrl);
    QString error;
    if(gestorCompetencias->altaParticipante(competenciaActual,datos,error)){
        QMessageBox* msg = new QMessageBox(a);
        msg->setText(error);
        QPixmap icono(":/images/Heros-verde-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
        return competenciaActual->getParticipantes();
    }
    else{
        QMessageBox* msg = new QMessageBox(a);
        msg->setText(error);
        QPixmap icono(":/images/Heros-rojo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
        QVector<Participante*> aux;
        return aux;
    }

}

Estado *GUI::buscarEstado(QString estado)
{
    for (int i = 0; i < estados.size(); ++i) {
        if(estado.toLower() == estados[i]->getNombre().toLower())
            return estados[i];
    }
    return NULL;
}

Deporte *GUI::buscarDeporte(QString deporte)
{
    for (int i = 0; i < deportes.size(); ++i) {
        if(deporte.toLower()==deportes[i]->getNombre().toLower())
            return deportes[i];
    }
    return NULL;
}

TipoModalidad *GUI::buscarTipoModalidad(QString tipoMod)
{
    for (int i = 0; i < modalidades.size(); ++i) {
        if(tipoMod.toLower() == modalidades[i]->getNombre().toLower())
            return modalidades[i];
    }
    return NULL;
}

void GUI::show()
{
    MainWindow * m = new MainWindow(this);
    m->show();
}

void MainWindow::on_pushButton_clicked()
{
    gui->handleMain(this,QString("registrarUsuario"));
}


EmailValidator::EmailValidator(QObject *parent) :
    QValidator(parent),
      m_validMailRegExp("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}"),
      m_intermediateMailRegExp("[a-z0-9._%+-]*@?[a-z0-9.-]*\\.?[a-z]*"){}

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
