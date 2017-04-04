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
  BOOST_CHECK_EQUAL(get_n_rows(m), sz);
  BOOST_CHECK_EQUAL(get_n_cols(m), sz);
}


BOOST_AUTO_TEST_CASE(maziak_Maze_mMaze)
{
  const auto sz = 11;
  const Maze m(sz);
  BOOST_CHECK_GT(FindExit(m).first , -1);
  BOOST_CHECK_GT(FindStart(m).first, -1);
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

BOOST_AUTO_TEST_CASE(maziak_CreateTestMaze1)
{
  const Maze m{CreateTestMaze1()};
  BOOST_CHECK(Count(MazeSquare::msPrisoner, m) > 0);
  BOOST_CHECK(Count(MazeSquare::msSword, m) > 0);
  BOOST_CHECK(Count(MazeSquare::msEnemy, m) > 0);
  BOOST_CHECK_EQUAL(Count(MazeSquare::msStart, m), 1);
  BOOST_CHECK_EQUAL(Count(MazeSquare::msExit, m), 1);
  const std::string measured{to_str(m.Get())};
  const std::string expected{
    "XXXXXXXXXXXXXXX\n"
    "X  +X+    X+  X\n"
    "X XXXXX XXXXX X\n"
    "X    ZX X  +X X\n"
    "XXX XXX X XXX X\n"
    "X:X X.X   XZ  X\n"
    "X X X X XXXXX X\n"
    "X             X\n"
    "XXXXX X X XXX X\n"
    "X     X X  ZX X\n"
    "X XXX X X XXXXX\n"
    "X   X X!X   X X\n"
    "XXX X XXXXX X X\n"
    "X   X     X   X\n"
    "XXXXXXXXXXXXXXX\n"
  };
  BOOST_CHECK_EQUAL(measured.size(), expected.size());
  BOOST_CHECK_EQUAL(measured, expected);
}

BOOST_AUTO_TEST_CASE(maziak_CreateTestMaze1_must_reproduce_same_maze_each_time)
{
  const Maze m{CreateTestMaze1()};
  const Maze n{CreateTestMaze1()};
  BOOST_CHECK_EQUAL(m, n);
}



