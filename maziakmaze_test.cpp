#include "maziakmaze.h"
#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_Maze_size)
{
  const auto sz = 11;
  const Maze m(sz);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}

BOOST_AUTO_TEST_CASE(maziak_Maze_CanGet)
{
  const auto sz = 11;
  const auto m = CreateIntMaze(sz);
  BOOST_CHECK( m.CanGet(0,0));
  BOOST_CHECK( m.CanGet(10,10));
  BOOST_CHECK(!m.CanGet( 0,11));
  BOOST_CHECK(!m.CanGet(11, 0));
  BOOST_CHECK(!m.CanGet(-1, 0));
  BOOST_CHECK(!m.CanGet( 0,-1));
}
