#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "gui.h"
#include "GestorBaseDatos.h"
#include "ui_mainwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, GUI guiP = new GUI(), GestorBaseDatos* gestorDBP = new GestorBaseDatos());
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    GUI gui;
    GestorBaseDatos gestorDB;

};

#endif // MAINWINDOW_H
