#include "listar_participante.h"
#include "ui_listar_participante.h"
#include "alta_participante.h"
#include "qpixmap.h"



listar_participante::listar_participante(GUI *guiP, Competencia *compP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listar_participante), competencia(compP), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);

    QPixmap userImg(":/images/user.png");
    ui->label_4->setPixmap(userImg);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    this->setWindowTitle("Listar Participantes de competencia");

    QRegExp nombre("[a-zA-Z0-9.'-]+( [a-zA-Z0-9.'-]+)*");
    QValidator* nomValidator = new QRegExpValidator(nombre,this);
    ui->lineEdit->setValidator(nomValidator);

    // validador del email
    EmailValidator* emailValidator = new EmailValidator(this);
    ui->lineEdit_2->setValidator(emailValidator);

    resize(300,400);
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->label_2->setText(compP->getNombre());

    participantes = compP->getParticipantes();
    // ocultar alta

    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < participantes.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantes[i]->getNombre()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantes[i]->getCorreo()));
    }
//    ui->tableWidget->resize(500,300);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0,"Participantes");
    ui->tabWidget->setTabText(1,"");
//    ui->tabWidget->setTabEnabled(0,false);
//    ui->tabWidget->setTabEnabled(1,false);

}

listar_participante::~listar_participante()
{
    delete ui;
}

void listar_participante::on_pushButton_clicked()
{
    this->close();
}

void listar_participante::on_pushButton_2_clicked()
{
    int actual = ui->tabWidget->currentIndex();

    if(actual == 0){

        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabText(0,"");
        ui->tabWidget->setTabText(1,"Nuevo Participante");
    }
    else{

    }

}


void listar_participante::on_pushButton_7_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0,"Participantes");
    ui->tabWidget->setTabText(1,"");
}

void listar_participante::on_tabWidget_currentChanged(int index)
{
    if(index == 0){
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->setTabText(0,"Participantes");
        ui->tabWidget->setTabText(1,"");
    }
}

void listar_participante::on_pushButton_8_clicked()
{
    QString email = ui->lineEdit_2->text();
    QString nombre = ui->lineEdit->text();


    // si la competencia esta creada o planificada se puede agregar participantes, sino no
    if(competencia->getEstado()->getNombre().toLower() == "creada"      ||
       competencia->getEstado()->getNombre().toLower() == "planificada"     )
    {
        // si el mail es valido y el nombre no es nulo se manda el participante nuevo y
        // se piden los participantes actualizados
        if(email != "" && nombre != "" && ui->lineEdit_2->hasAcceptableInput() ){

            QVector<Participante*> participantesActualizados = gui->handleAltaParticipante(this,nombre,email,imgUrl);
            if(participantesActualizados.size() != 0){

                ui->tableWidget->setRowCount(0);
                for (int i = 0; i < participantesActualizados.size(); ++i) {
                    ui->tableWidget->insertRow(i);
                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(participantesActualizados[i]->getNombre()));
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(participantesActualizados[i]->getCorreo()));
                }
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                participantes = participantesActualizados;
                ui->tableWidget->resizeColumnsToContents();
                this->on_pushButton_7_clicked();
            }
        }
        else{
            QMessageBox* msg = new QMessageBox(this);
            msg->setText("Por favor complete correctamente todos los campos obligatorios");
            QPixmap icono(":/images/Heros-amarillo-64.png");
            msg->setIconPixmap(icono);
            msg->setModal(true);
            msg->exec();
        }

    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("No se puede agregar participantes a la competencia");
        QPixmap icono(":/images/Heros-rojo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();
    }

}

void listar_participante::on_pushButton_6_clicked()
{
    imgUrl = "";
    imgUrl = QFileDialog::getOpenFileName(this,tr("elija una imagen"),"",tr("Imágenes (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(imgUrl.size() > 0){
        QPixmap img(imgUrl);
        ui->label_4->setPixmap(img.scaled(128, 128, Qt::IgnoreAspectRatio, Qt::FastTransformation));
    }
}
