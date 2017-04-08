#ifndef QTMAZIAKGAMEWONDIALOG_TEST_H
#define QTMAZIAKGAMEWONDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtGameWonDialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void display();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKGAMEWONDIALOG_TEST_H
