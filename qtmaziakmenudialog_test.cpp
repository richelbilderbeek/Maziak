#include "qtmaziakmenudialog_test.h"

#include <cassert>

#include "qtmaziakmenudialog.h"
#include "ui_qtmaziakmenudialog.h"

void ribi::maziak::QtMenuDialog_test::about_is_triggered_by_a()
{
  QtMenuDialog d;
  d.show();
  d.DisablePopups();
  QTest::keyClick(
    &d,
    Qt::Key_A,
    Qt::NoModifier
  );
}

void ribi::maziak::QtMenuDialog_test::display()
{
  QtMenuDialog d;
  QTimer::singleShot(1000, &d, SLOT(close()));
  d.exec();
}

void ribi::maziak::QtMenuDialog_test::down_increases_difficulty()
{
  QtMenuDialog d;
  d.show();
  assert(d.GetDifficulty() == Difficulty::easy);
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  assert(d.GetDifficulty() == Difficulty::medium);
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  QVERIFY(d.GetDifficulty() == Difficulty::hard);
  //Down again and nothing happens
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  QVERIFY(d.GetDifficulty() == Difficulty::hard);
}

void ribi::maziak::QtMenuDialog_test::instructions_is_triggered_by_i()
{
  QtMenuDialog d;
  d.show();
  d.DisablePopups();
  QTest::keyClick(
    &d,
    Qt::Key_I,
    Qt::NoModifier
  );
}

void ribi::maziak::QtMenuDialog_test::quit_is_triggered_by_esc()
{
  QtMenuDialog d;
  d.show();
  d.DisablePopups();
  QTest::keyClick(
    &d,
    Qt::Key_Escape,
    Qt::NoModifier
  );
}

void ribi::maziak::QtMenuDialog_test::quit_is_triggered_by_q()
{
  QtMenuDialog d;
  d.show();
  d.DisablePopups();
  QTest::keyClick(
    &d,
    Qt::Key_Q,
    Qt::NoModifier
  );
}

void ribi::maziak::QtMenuDialog_test::set_difficulty_to_easy_with_keyboard()
{
  QtMenuDialog d;
  d.show();
  QTest::keyClick(
    &d,
    Qt::Key_Down,
    Qt::NoModifier
  );
  assert(d.GetDifficulty() != Difficulty::easy);
  QTest::keyClick(
    &d,
    Qt::Key_Up,
    Qt::NoModifier
  );
  QVERIFY(d.GetDifficulty() == Difficulty::easy);
}

void ribi::maziak::QtMenuDialog_test::set_difficulty_to_hard_with_keyboard()
{
  QtMenuDialog d;
  d.show();
  assert(d.GetDifficulty() != Difficulty::hard);
  QTest::keyClick(
    &d,
    Qt::Key_Down,
    Qt::NoModifier
  );
  QTest::keyClick(
    &d,
    Qt::Key_Down,
    Qt::NoModifier
  );
  QVERIFY(d.GetDifficulty() == Difficulty::hard);
}

void ribi::maziak::QtMenuDialog_test::set_difficulty_to_medium_with_keyboard()
{
  QtMenuDialog d;
  d.show();
  assert(d.GetDifficulty() != Difficulty::medium);
  QTest::keyClick(
    &d,
    Qt::Key_Down,
    Qt::NoModifier
  );
  QVERIFY(d.GetDifficulty() == Difficulty::medium);
}


void ribi::maziak::QtMenuDialog_test::set_difficulty_to_easy_with_mouse()
{
  QtMenuDialog d;
  d.show();
  QTest::mouseClick(
    &d,
    Qt::LeftButton,
    Qt::NoModifier,
    d.GetUi().widget_hard->geometry().center()
  );
  assert(d.GetDifficulty() != Difficulty::easy);
  QTest::mouseClick(
    &d,
    Qt::LeftButton,
    Qt::NoModifier,
    d.GetUi().widget_easy->geometry().center()
  );
  QVERIFY(d.GetDifficulty() == Difficulty::easy);
}

void ribi::maziak::QtMenuDialog_test::set_difficulty_to_hard_with_mouse()
{
  QtMenuDialog d;
  d.show();
  assert(d.GetDifficulty() != Difficulty::hard);
  QTest::mouseClick(
    &d,
    Qt::LeftButton,
    Qt::NoModifier,
    d.GetUi().widget_hard->geometry().center()
  );
  QVERIFY(d.GetDifficulty() == Difficulty::hard);
}

void ribi::maziak::QtMenuDialog_test::set_difficulty_to_medium_with_mouse()
{
  QtMenuDialog d;
  d.show();
  assert(d.GetDifficulty() != Difficulty::medium);
  QTest::mouseClick(
    &d,
    Qt::LeftButton,
    Qt::NoModifier,
    d.GetUi().widget_medium->geometry().center()
  );
  QVERIFY(d.GetDifficulty() == Difficulty::medium);
}

void ribi::maziak::QtMenuDialog_test::start_is_triggered_by_s()
{
  QtMenuDialog d;
  d.show();
  d.DisablePopups();
  QTest::keyClick(
    &d,
    Qt::Key_S,
    Qt::NoModifier
  );
}


void ribi::maziak::QtMenuDialog_test::up_decreases_difficulty()
{
  QtMenuDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  QTest::keyClick(&d, Qt::Key_Down, Qt::NoModifier);
  assert(d.GetDifficulty() == Difficulty::hard);
  QTest::keyClick(&d, Qt::Key_Up, Qt::NoModifier);
  assert(d.GetDifficulty() == Difficulty::medium);
  QTest::keyClick(&d, Qt::Key_Up, Qt::NoModifier);
  assert(d.GetDifficulty() == Difficulty::easy);
  //Up again and nothing happens
  QTest::keyClick(&d, Qt::Key_Up, Qt::NoModifier);
  assert(d.GetDifficulty() == Difficulty::easy);
}
