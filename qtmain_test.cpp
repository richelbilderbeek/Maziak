#include "qtmaziaksprites_test.h"
#include "qtmaziakdisplay_test.h"
#include <iostream>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  //I am most interested in:

  //These are all tests in alphabetical order
  { ribi::maziak::QtDisplay_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtSprites_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
