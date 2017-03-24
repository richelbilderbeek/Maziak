#include "maziakgame.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_MainDialog_construction)
{
  const Game g{CreateTestMaze1()};
  BOOST_CHECK(!g.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(maziak_MainDialog_stream_out)
{
  const Game g{CreateTestMaze1()};
  std::stringstream s;
  s << g;
  const auto t = to_str(g);
  BOOST_CHECK(!s.str().empty());
  BOOST_CHECK_EQUAL(s.str(), t);
}

BOOST_AUTO_TEST_CASE(maziak_CreateTestMainDialog1)
{
  const auto g = CreateTestGame1();
  const auto m1 = g.GetMaze().Get();
  const auto m2 = CreateTestMaze1().Get();
  BOOST_CHECK_EQUAL(m1, m2);
}

