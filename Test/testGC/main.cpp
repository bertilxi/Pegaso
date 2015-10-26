#include <QCoreApplication>
#include <QTest>
#include "testgestorpartido.h"

int main(int argc, char** argv)
{
   int status = 0;
   {  testGestorPartido tc;
      status |= QTest::qExec(&tc, argc, argv);
      //testGestorPartido tc;
      //     status |= QTest::qExec(&tc, argc, argv);

   }
   return status;
}
