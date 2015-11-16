#include "registrar_usuario.h"
#include "ui_registrar_usuario.h"
#include "qpixmap.h"

registrar_usuario::registrar_usuario(GUI *guiP, QVector<Pais *> paisesP, QWidget *parent):
    QDialog(parent), ui(new Ui::registrar_usuario), gui(guiP), paises(paisesP)
{
    ui->setupUi(this);
    QPixmap pix("/home/fer/Pegaso/Heros64.png");
    ui->label_logo->setPixmap(pix);
    ui->lineEdit_6->setEnabled(true);

    for (int i = 0; i < paises.size(); ++i) {
       ui->comboBox_5->addItem(paises[i]->getNombre());
    }
    ui->comboBox_8->setCurrentIndex(-1);
    ui->comboBox_5->setCurrentIndex(-1);
    ui->comboBox_6->setCurrentIndex(-1);

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
        msg->setText(error);
        msg->show();
    }
    else
    {
        QString errorStr = errores[0];
        for (int i = 1; i < errores.size(); ++i) {
           errorStr += "\n" + errores[i] ;
        }
        QMessageBox* msg = new QMessageBox(this);
        msg->setModal(true);
        msg->setText(errorStr);
        msg->show();
    }
}

void registrar_usuario::on_comboBox_5_currentIndexChanged(int index)
{
    ui->comboBox_8->clear();
    if( index != -1){
        provincias = gui->getProvincias(paises[index]);
        qDebug()<<"provincias size "<<provincias.size();

        for (int i = 0; i < provincias.size(); ++i) {
            ui->comboBox_8->addItem(provincias[i]->getNombre());
        }
    }
}

void registrar_usuario::on_comboBox_8_currentIndexChanged(int index)
{
    ui->comboBox_6->clear();
    if( index != -1){
        localidades = gui->getLocalidades(provincias[index]);

        for (int i = 0; i < localidades.size(); ++i) {
           ui->comboBox_6->addItem(localidades[index]->getNombre());
        }
    }
}
