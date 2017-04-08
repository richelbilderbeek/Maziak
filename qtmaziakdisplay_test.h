#ifndef QTMAZIAKDISPLAY_TEST_H
#define QTMAZIAKDISPLAY_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtDisplay_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void constructor();
  void display();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKDISPLAY_TEST_H
