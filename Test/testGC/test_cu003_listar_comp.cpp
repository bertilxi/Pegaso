/*
#include <QtTest/QtTest>
// agregar cabeceras de DTO's

class test_listar_comp: public QObject
{
    Q_OBJECT
private slots:
    void getCompLazy(user,filtros);
};


// ejemplo
void test_listar_comp::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void test_listar_comp::getCompLazy(user, filtros)
{
    QString user = "";// Generar usuarios o tomar de gestor usuarios
    QVector<QString> filtros[4] ; // Ver posibles filtros y generarlos
    // dto no linkeado todavia
    DtoCompetencia a(user,filtros);

}

QTEST_MAIN(TestQString)
#include "testqstring.moc"
*/
