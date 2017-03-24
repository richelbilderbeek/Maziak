#include "maziakterminal.h"

#include "maziakgame.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_SolutionMaze_size)
{
  const Terminal t{CreateTestTerminal1()};
  BOOST_CHECK(!to_str(t).empty());
}

BOOST_AUTO_TEST_CASE(terminal_TogglePrisoners_must_animate)
{
  Terminal t{CreateTestTerminal1()};
  const auto before = to_str(t);
  t.TogglePrisoners();
  const auto after = to_str(t);
  BOOST_CHECK_NE(before, after);
  t.TogglePrisoners();
  const auto before_again = to_str(t);
  BOOST_CHECK_NE(before_again, after);
  BOOST_CHECK_EQUAL(before_again, before);
}
