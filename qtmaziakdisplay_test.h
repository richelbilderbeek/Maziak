#ifndef QTMAZIAKDISPLAY_TEST_H
#define QTMAZIAKDISPLAY_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtDisplay_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void display();
  void view_width_is_nine();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKDISPLAY_TEST_H
