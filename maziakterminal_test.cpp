#include "maziakterminal.h"

#include "maziakmaindialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_SolutionMaze_size)
{
  MainDialog dialog{7 + (4 * 2), 234};
  Terminal terminal;
  dialog.SetDisplay(&terminal);
  //dialog.Tick();
  terminal.DoDisplay(dialog);

}
