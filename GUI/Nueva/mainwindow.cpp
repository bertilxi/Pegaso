#include "mainwindow.h"

MainWindow::MainWindow(GUI* guiP, GestorBaseDatos *gestorDBP, QWidget *parent):
    QMainWindow(parent), gui(guiP), gestorDB(gestorDBP) ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // se encripta la contraseña a penas se pide por seguridad
    QString password = ui->lineEdit_2->text();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    qDebug() << hash.result().toHex();
    QString passwordEncriptada = hash.result().toHex();
    QString email = ui->lineEdit->text();
    QVector<QString> args;
    args.append(email);
    args.append(passwordEncriptada);
    // se envian datos se pide la accion correspondiente
    gui->handleMain(this,QString("pantallaUsuario"),args);
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
    qDebug()<<"se cerro el programa";
}
