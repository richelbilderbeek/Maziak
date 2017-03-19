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
}

BOOST_AUTO_TEST_CASE(maziak_ConvertMaze)
{
  const auto sz = 11;
  const int rng_seed{42};
  /// 0 : path
  /// 1 : wall
  const auto m = CreateIntMaze(sz, rng_seed);
  // msEmpty,
  // msWall,
  const auto n = ConvertMaze(m);
  BOOST_CHECK_EQUAL(Count(0, m), Count(MazeSquare::msEmpty, n));
  BOOST_CHECK_EQUAL(Count(1, m), Count(MazeSquare::msWall, n));
}

BOOST_AUTO_TEST_CASE(maziak_Maze_constructor_of_interesting_maze)
{
  const auto sz = 15;
  const int rng_seed{145};
  const Maze m(sz, rng_seed);
  BOOST_CHECK(Count(MazeSquare::msPrisoner1, m) > 0);
  BOOST_CHECK(Count(MazeSquare::msSword, m) > 0);
  BOOST_CHECK(Count(MazeSquare::msEnemy1, m) > 0);
  BOOST_CHECK_EQUAL(Count(MazeSquare::msStart, m), 1);
  BOOST_CHECK_EQUAL(Count(MazeSquare::msExit, m), 1);
  const std::string measured{ToStr(m.Get())};
  const std::string expected{
    "XXXXXXXXXXXXXXX\n"
    "X!X+X   X  +XZX\n"
    "X X XXX X XXX X\n"
    "X X   X X     X\n"
    "X X XXX X XXXXX\n"
    "X X X        .X\n"
    "X X XXX XXXXXXX\n"
    "X   X+        X\n"
    "XXX XXX X XXX X\n"
    "X       X   X X\n"
    "X X X XXXXX X X\n"
    "X:X X     X XZX\n"
    "XXX X XXX XXXXX\n"
    "X   X  ZX    +X\n"
    "XXXXXXXXXXXXXXX\n"
  };
  BOOST_CHECK_EQUAL(measured.size(), expected.size());
  BOOST_CHECK_EQUAL(measured, expected);
}

