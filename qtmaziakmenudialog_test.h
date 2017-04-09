#ifndef QTMAZIAKMENUDIALOG_TEST_H
#define QTMAZIAKMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace maziak {

class QtMenuDialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void about_is_triggered_by_a();
  void display();
  void down_increases_difficulty();
  void instructions_is_triggered_by_i();
  void quit_is_triggered_by_esc();
  void quit_is_triggered_by_q();
  void set_difficulty_to_easy_with_keyboard();
  void set_difficulty_to_hard_with_keyboard();
  void set_difficulty_to_medium_with_keyboard();
  void set_difficulty_to_easy_with_mouse();
  void set_difficulty_to_hard_with_mouse();
  void set_difficulty_to_medium_with_mouse();
  void start_is_triggered_by_s();
  void up_decreases_difficulty();
};

} //~namespace maziak
} //~namespace ribi

#endif // QTMAZIAKMENUDIALOG_TEST_H
