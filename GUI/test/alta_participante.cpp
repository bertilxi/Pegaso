#include "alta_participante.h"
#include "ui_alta_participante.h"
#include "qpixmap.h"

alta_participante::alta_participante(GUI *guiP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alta_participante), gui(guiP)
{

    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    QRegExp nombre("[a-zA-Z0-9.-]*");
    QValidator* nomValidator = new QRegExpValidator(nombre,this);
    ui->lineEdit->setValidator(nomValidator);

    // validador del email
    EmailValidator* emailValidator = new EmailValidator(this);
    ui->lineEdit_2->setValidator(emailValidator);

}

alta_participante::~alta_participante()
{
    delete ui;
}

void alta_participante::on_pushButton_3_clicked()
{
    this->close();
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

void alta_participante::on_pushButton_2_clicked()
{
    QString email = ui->lineEdit_2->text();
    QString nombre = ui->lineEdit->text();

    // tomar ruta de imagen

    QString imgUrl = "";

    gui->handleAltaParticipante(this,nombre,email,imgUrl);

}

void alta_participante::on_pushButton_clicked()
{

}
