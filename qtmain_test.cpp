#include "qtmaziakdisplay_test.h"
#include "qtmaziakgameoverdialog_test.h"
#include "qtmaziakgamewondialog_test.h"
#include "qtmaziakinstructionsdialog_test.h"
#include "qtmaziakmenudialog_test.h"
#include "qtmaziaksprites_test.h"
#include <iostream>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  //I am most interested in:

  //These are all tests in alphabetical order
  { ribi::maziak::QtDisplay_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtGameOverDialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtGameWonDialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtInstructionsDialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtMenuDialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::maziak::QtSprites_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
