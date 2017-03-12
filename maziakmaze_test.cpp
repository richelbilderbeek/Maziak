#include "maziakmaze.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "maziakhelper.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_Maze_size)
{
  const auto sz = 11;
  const Maze m(sz);
  BOOST_CHECK(IsSquare(m));
  BOOST_CHECK_EQUAL(GetSize(m), sz);
}


BOOST_AUTO_TEST_CASE(maziak_Maze_mMaze)
{
  const auto sz = 11;
  const Maze m(sz);
  BOOST_CHECK(IsSquare(m.Get()));
  BOOST_CHECK_GT(m.FindExit().first , -1);
  BOOST_CHECK_GT(m.FindStart().first, -1);
}

BOOST_AUTO_TEST_CASE(maziak_Maze_get_and_set_must_be_symmetrical)
{
  const auto sz = 11;
  Maze m(sz);
  assert(m.CanSet(3,4));
  m.Set(3,4,MazeSquare::msEmpty);
  BOOST_CHECK_EQUAL(m.Get(3,4), MazeSquare::msEmpty);
  m.Set(3,4,MazeSquare::msWall);
  BOOST_CHECK_EQUAL(m.Get(3,4), MazeSquare::msWall);
}

BOOST_AUTO_TEST_CASE(maziak_Maze_stream_out)
{
  const auto sz = 11;
  Maze m(sz);
  std::stringstream s;
  s << m;
  BOOST_CHECK(!s.str().empty());
  std::cout << m;
}
