#include "qtmaziakmenudialog_test.h"
#include "qtmaziakmenudialog.h"

void ribi::maziak::QtMenuDialog_test::display()
{
  const int rng_seed{42};
  QtMenuDialog d(rng_seed);
  d.show();
}
