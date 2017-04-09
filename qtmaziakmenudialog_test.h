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
  void set_difficulty_to_hard_with_keyboard();
  void set_difficulty_to_medium_with_keyboard();
  void set_difficulty_to_hard_with_mouse();
  void set_difficulty_to_medium_with_mouse();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG_TEST_H
