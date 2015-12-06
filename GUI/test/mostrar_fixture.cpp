#include "mostrar_fixture.h"
#include "ui_mostrar_fixture.h"
#include "gestionar_fixture.h"
#include "qpixmap.h"

mostrar_fixture::mostrar_fixture(GUI *guiP, Competencia *comp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mostrar_fixture), competencia(comp), gui(guiP)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);
    this->setWindowTitle("Mostrar Fixture de competencia");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < comp->getPartidos().size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(comp->getPartidos()[i]->getFecha())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoA()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(comp->getPartidos()[i]->getEquipoB()->getNombre()));
        QString resultadoA = "" ;
        QString resultadoB = "" ;
        QString resultadoPartido = "";



        if(comp->getPartidos()[i]->getActual() != NULL){
            resultadoA = comp->getPartidos()[i]->getActual()->getResultadoA()->getNombre().toLower();
            resultadoB = comp->getPartidos()[i]->getActual()->getResultadoB()->getNombre().toLower();

            if( resultadoA == "ganó" ){
                resultadoPartido = "Ganó el equipo A";
            }
            else if( resultadoB == "ganó" ){
                resultadoPartido = "Ganó el equipo B";
            }
            else if(resultadoA == "empate"){
                resultadoPartido = "Empate";
            }
<<<<<<< HEAD
            else if(resultadoA == "no se presentó"){
                if(resultadoB == "no se presentó"){

                    resultadoPartido = "Partido Cancelado";
                }
                else{
                    resultadoPartido = "Ganó el equipo B";
                }
            }
            else if(resultadoB == "no se presentó"){
                if(resultadoA == "no se presentó"){

                    resultadoPartido = "Partido Cancelado";
                }
                else{
                    resultadoPartido = "Ganó el equipo A";
                }
            }

            if(comp->getPartidos()[i]->getActual() != NULL){
                resultadoA = comp->getPartidos()[i]->getActual()->getResultadoA()->getNombre().toLower();
            }
            if(comp->getPartidos()[i]->getActual() != NULL){
                resultadoB = comp->getPartidos()[i]->getActual()->getResultadoB()->getNombre().toLower();
            }
            if( resultadoA == "ganó" ){
                resultadoPartido = "Ganó el equipo A";
            }
            else if( resultadoA == "ganó" ){
                resultadoPartido = "Ganó el equipo A";
            }
            else if(resultadoA == "empató"){
                resultadoPartido = "Ganó el equipo B";

=======
            else if(resultadoA == "no se presentó" && resultadoB == "no se presentó"){
                resultadoPartido = "Ninguno se presentó";
            }
            else{
                    resultadoPartido = "Error";
>>>>>>> 948d221a38c8d6bbc51b3b2f2c6eabbc0a0aa298
            }


        }

        ui->tableWidget->setItem(i,3,new QTableWidgetItem(resultadoPartido));

    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resize(200,450);
    ui->tableWidget->setCurrentCell(-1,-1);
}

mostrar_fixture::~mostrar_fixture()
{
    delete ui;
}

void mostrar_fixture::on_pushButton_clicked()
{
    this->close();
}



void mostrar_fixture::on_pushButton_2_clicked()
{
    int partidoSeleccionado = ui->tableWidget->currentRow();

    if(partidoSeleccionado > -1){

        Partido* p = competencia->getPartidos()[partidoSeleccionado];
        gui->handleMostrarFixture(this,"gestionarFixture",p);
    }
    else{
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Por favor seleccione un partido");
        QPixmap icono(":/images/Heros-amarillo-64.png");
        msg->setIconPixmap(icono);
        msg->setModal(true);
        msg->exec();

    }

}
