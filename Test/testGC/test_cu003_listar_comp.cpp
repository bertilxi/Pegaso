#include <QtTest/QtTest>

class test_listar_comp: public QObject
{
    Q_OBJECT
private slots:
    void getCompLazy(user,filtros);
};

void test_listar_comp::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}



void test_listar_comp::getCompLazy(user, filtros)
{
    QString user = "";// Generar usuarios o tomar de gestor usuarios
    QVector<QString> filtros ; // Ver posibles filtros y generarlos

}

QTEST_MAIN(TestQString)
#include "testqstring.moc"
