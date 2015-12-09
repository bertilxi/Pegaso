#include "mostrar_fixture.h"
#include "ui_mostrar_fixture.h"
#include "gestionar_fixture.h"
#include "qpixmap.h"

bool comparePartido(Partido* a, Partido* b) { return (a->getFecha() < b->getFecha()); }

mostrar_fixture::mostrar_fixture(GUI *guiP, Competencia *comp,ver_competencia* vc, QWidget *parent):
    QDialog(parent),
    ui(new Ui::mostrar_fixture), competencia(comp), gui(guiP), verCompetencia(vc)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Heros64.png");
    ui->label_logo->setPixmap(pix);
    this->setWindowTitle("Mostrar Fixture de competencia");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QVector<Partido*> partidos = comp->getPartidos();

     qSort(partidos.begin(),partidos.end(),comparePartido);
     comp->setPartidos(partidos);

    for (int i = 0; i < partidos.size(); ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(partidos[i]->getFecha())));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(partidos[i]->getEquipoA()->getNombre()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(partidos[i]->getEquipoB()->getNombre()));
        QString resultadoA = "" ;
        QString resultadoB = "" ;
        QString resultadoPartido = "";



        if(comp->getPartidos()[i]->getActual() != NULL){
            resultadoA = comp->getPartidos()[i]->getActual()->getResultadoA()->getNombre().toLower();
            resultadoB = comp->getPartidos()[i]->getActual()->getResultadoB()->getNombre().toLower();
            qDebug() << comp->getPartidos()[i]->getActual()->getResultadoA()->getNombre();
            qDebug() << resultadoA;
            if( resultadoA == "ganó" ){
                resultadoPartido = "Ganó el equipo A";
            }
            else if( resultadoB == "ganó" ){
                resultadoPartido = "Ganó el equipo B";
            }
            else if(resultadoA == "empate"){
                resultadoPartido = "Empate";
            }
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
        }

        ui->tableWidget->setItem(i,3,new QTableWidgetItem(resultadoPartido));

    }
    ui->tableWidget->resizeColumnsToContents();
    int width = (ui->tableWidget->columnCount() - 1) + ui->tableWidget->verticalHeader()->width();
    for(int column = 0; column < ui->tableWidget->columnCount(); column++)
    width = width + ui->tableWidget->columnWidth(column);
    width+=20;
    ui->tableWidget->setMinimumWidth(width);
    this->resize(sizeHint().width(),450);
    ui->tableWidget->setCurrentCell(-1,-1);
}

mostrar_fixture::~mostrar_fixture()
{
    delete ui;
}

void mostrar_fixture::actualizarTabla()
{
    // actualizamos la tabla
    Competencia* comp = competencia;
    ui->tableWidget->setRowCount(0);
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
            else resultadoPartido = "Error";
        }

        ui->tableWidget->setItem(i,3,new QTableWidgetItem(resultadoPartido));

    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setCurrentCell(-1,-1);
}

void mostrar_fixture::on_pushButton_clicked()
{
    this->close();
    verCompetencia->actualizar(competencia);
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

