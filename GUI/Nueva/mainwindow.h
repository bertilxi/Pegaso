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
    explicit MainWindow(GUI guiP, GestorBaseDatos* gestorDBP,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    GUI gui;
    GestorBaseDatos* gestorDB;

};

#endif // MAINWINDOW_H
