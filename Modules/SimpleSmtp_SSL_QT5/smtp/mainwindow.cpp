#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    sendMail();
}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("pegasocompetencias@gmail.com", "pancho2000", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("Competencias Pegaso", "d.campodonico@hotmail.com" , "Se ha eliminado una competencia","La competencia id_comp ha sido eliminada");
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}
