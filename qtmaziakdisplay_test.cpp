#include "qtmaziakdisplay_test.h"
#include "qtmaziakdisplay.h"
#include "maziakgame.h"

void ribi::maziak::QtDisplay_test::constructor()
{
  const int n_cols{7};
  const int n_rows{11};
  const int rng_seed{42};
  const int view_width{9};
  const int view_height{13};
  const QtDisplay q(n_cols, n_rows, rng_seed, view_width, view_height);
  //Cannot test this in constructor: never call virtual functions in a class constructor
  QVERIFY(get_n_cols(q) == n_cols);
  QVERIFY(get_n_rows(q) == n_rows);
  QVERIFY(q.GetViewHeight() == view_height);
  QVERIFY(q.GetViewWidth() == view_width);
}

void ribi::maziak::QtDisplay_test::display()
{
  const int n_cols{7};
  const int n_rows{11};
  const int rng_seed{42};
  const int view_width{9};
  const int view_height{13};
  QtDisplay q(n_cols, n_rows, rng_seed, view_width, view_height);
  q.show();
}
