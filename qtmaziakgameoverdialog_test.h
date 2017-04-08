#ifndef QTMAZIAKGAMEOVERDIALOG_TEST_H
#define QTMAZIAKGAMEOVERDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtGameOverDialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void display();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKGAMEOVERDIALOG_TEST_H
