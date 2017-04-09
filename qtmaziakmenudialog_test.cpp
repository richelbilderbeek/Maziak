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
  d.show();
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


