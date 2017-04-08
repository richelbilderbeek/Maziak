#ifndef QTMAZIAKMENUDIALOG_TEST_H
#define QTMAZIAKMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtMenuDialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void display();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG_TEST_H
