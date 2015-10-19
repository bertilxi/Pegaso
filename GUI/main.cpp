#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
/*
    Codificacion necesaria para acentos en las interfaces, por el momentos da error de compilacion
*/
//    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForTr(linuxCodec);
//    QTextCodec::setCodecForCStrings(linuxCodec);
//    QTextCodec::setCodecForLocale(linuxCodec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
