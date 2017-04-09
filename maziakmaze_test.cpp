#include "maziakmaze.h"

#include <cassert>
#include <sstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "maziakhelper.h"

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_Maze_size)
{
  const auto n_cols = 7;
  const auto n_rows = 11;
  const auto rng_seed = 42;
  const Maze m(n_cols, n_rows, rng_seed);
  BOOST_CHECK_EQUAL(get_n_rows(m), n_rows);
  BOOST_CHECK_EQUAL(get_n_cols(m), n_cols);
}


BOOST_AUTO_TEST_CASE(maziak_Maze_mMaze)
{
  const auto sz = 11;
  const auto rng_seed = 42;
  const Maze m(sz, sz, rng_seed);
  BOOST_CHECK_GT(FindExit(m).first , -1);
  BOOST_CHECK_GT(FindStart(m).first, -1);
}

BOOST_AUTO_TEST_CASE(maziak_Maze_get_and_set_must_be_symmetrical)
{
  const auto sz = 11;
  const auto rng_seed = 42;
  Maze m(sz, sz, rng_seed);
  assert(m.CanSet(3,4));
  m.Set(3,4,MazeSquare::empty);
  BOOST_CHECK_EQUAL(m.Get(3,4), MazeSquare::empty);
  m.Set(3,4,MazeSquare::wall);
  BOOST_CHECK_EQUAL(m.Get(3,4), MazeSquare::wall);
}

BOOST_AUTO_TEST_CASE(maziak_Maze_stream_out)
{
  const auto sz = 11;
  const auto rng_seed = 42;
  const Maze m(sz, sz, rng_seed);
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
  const auto m = CreateIntMaze(sz, sz, rng_seed);
  // msEmpty,
  // msWall,
  const auto n = ConvertMaze(m);
  BOOST_CHECK_EQUAL(Count(0, m), Count(MazeSquare::empty, n));
  BOOST_CHECK_EQUAL(Count(1, m), Count(MazeSquare::wall, n));
}

BOOST_AUTO_TEST_CASE(maziak_CreateTestMaze1)
{
  const Maze m{CreateTestMaze1()};
  BOOST_CHECK(Count(MazeSquare::prisoner, m) > 0);
  BOOST_CHECK(Count(MazeSquare::sword, m) > 0);
  BOOST_CHECK(Count(MazeSquare::enemy, m) > 0);
  BOOST_CHECK_EQUAL(Count(MazeSquare::start, m), 1);
  BOOST_CHECK_EQUAL(Count(MazeSquare::exit, m), 1);
  const std::string measured{to_str(m.Get())};
  const std::string expected{
    "XXXXXXXXXXXXXXXXXXX\n"
    "X!  X X+X.      X X\n"
    "XXX X X XXX XXXXX X\n"
    "XZX X X XZ  X:X X X\n"
    "X X X X XXX X X X X\n"
    "X   X X         X X\n"
    "X XXX XXX XXXXXXX X\n"
    "X                 X\n"
    "X X XXXXX XXX XXXXX\n"
    "X X X X X  +X     X\n"
    "X XXX XXX XXX XXXXX\n"
    "X X         X     X\n"
    "X X X X XXX XXXXX X\n"
    "X X+X X+X    ZX   X\n"
    "XXXXXXXXXXXXXXXXXXX\n"
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



