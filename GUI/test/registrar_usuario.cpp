#include "registrar_usuario.h"
#include "ui_registrar_usuario.h"
#include "qpixmap.h"

registrar_usuario::registrar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registrar_usuario)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
}

registrar_usuario::registrar_usuario(GUI *guiP, QWidget *parent):
    QDialog(parent), ui(new Ui::registrar_usuario), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
    ui->lineEdit_6->setEnabled(true);

}

registrar_usuario::~registrar_usuario()
{
    delete ui;
}

void registrar_usuario::on_pushButton_2_clicked()
{
     this->close();
}

void registrar_usuario::on_pushButton_clicked()
{
    QStringList errores;
    QString c1 = ui->lineEdit_2->text();
    QString c2 = ui->lineEdit_3->text();

    if(c1 != c2){
        errores.append("Su contraseña no coincide, por favor coloquela nuevamente.");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }

    QString correo = ui->lineEdit_6->text();
    QString nombre = ui->lineEdit_9->text();
    QString apellido = ui->lineEdit_10->text();
    QString tipoDocumento = ui->comboBox_7->currentText();
    QString documento = ui->lineEdit_8->text();
    QString pais = ui->comboBox_5->currentText();
    QString provincia = ui->comboBox_8->currentText();
    QString localidad = ui->comboBox_6->currentText();
    bool terminos = ui->checkBox->isChecked();

    if(terminos != 1){
        errores.append("Por favor lea y acepte los Terminos de servicio para continuar.");
    }

    if(errores.size() == 0){
        QByteArray passwordHash = QCryptographicHash::hash(QByteArray::fromStdString(ui->lineEdit_2->text().toStdString()),QCryptographicHash::Sha256);
        DtoUsuario * data = new DtoUsuario(correo,nombre,apellido,tipoDocumento,documento,pais,provincia,localidad,passwordHash);

        QString error = gui->handleRegistrarUsuario(data);
        QMessageBox* msg = new QMessageBox(this);
        msg->setModal(true);
        msg->show();

    }
}
