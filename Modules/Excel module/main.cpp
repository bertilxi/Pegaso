#include <QCoreApplication>
#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxformat.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
       QXlsx::Document xlsx;
       QXlsx::Format format1;
       format1.setFontColor(QColor(Qt::red));
       format1.setPatternBackgroundColor(QColor(Qt::lightGray));
       xlsx.write("A1", "Hello Qt!",format1);
       xlsx.saveAs("Test.xlsx");
    return 0;
}
