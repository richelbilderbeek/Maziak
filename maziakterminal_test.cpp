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

BOOST_AUTO_TEST_CASE(terminal_stepping_on_prisoner_must_reveal_solution)
{
/*
    0123456789012345678

 0  XXXXXXXXXXXXXXXXXXX
 1  X!  X X+X.      X X
 2  XXX X X XXX XXXXX X
 3  XZX X X XZ  X:X X X
 4  X X X X XXX X X X X
 5  X   X X         X X
 6  X XXX XXX XXXXXXX X
 7  X                 X
 8  X X XXXXX XXX XXXXX
 9  X X X X X  +X     X
10  X XXX XXX XXX XXXXX
11  X X         X     X
12  X X X X XXX XXXXX X
13  X X+X X+X    ZX   X
14  XXXXXXXXXXXXXXXXXXX

*/

  Terminal t{CreateTestTerminal1()};
  BOOST_CHECK(!t.GetDoShowSolution());
  t.PressKey(Key::right);
  t.PressKey(Key::right);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::right);
  t.PressKey(Key::right);
  t.PressKey(Key::up);
  t.PressKey(Key::up);
  BOOST_CHECK(!t.GetDoShowSolution());
  assert(t.GetPlayerSquare() == MazeSquare::msPrisoner);
  t.RespondToCurrentSquare();
  BOOST_CHECK(t.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(terminal_solution_must_reveal_temporarily)
{
  Terminal t{CreateTestTerminal1()};
  t.PressKey(Key::right);
  t.PressKey(Key::right);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::right);
  t.PressKey(Key::right);
  t.PressKey(Key::up);
  t.PressKey(Key::up);
  t.RespondToCurrentSquare();
  assert(t.GetDoShowSolution());
  for (int i=0; i!=100; ++i)
  {
    t.Tick();
  }
  assert(!t.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(terminal_AnimateFighting_must_animate)
{
/*
    0123456789012345678

 0  XXXXXXXXXXXXXXXXXXX
 1  X!  X X+X.      X X
 2  XXX X X XXX XXXXX X
 3  XZX X X XZ  X:X X X
 4  X X X X XXX X X X X
 5  X   X X         X X
 6  X XXX XXX XXXXXXX X
 7  X                 X
 8  X X XXXXX XXX XXXXX
 9  X X X X X  +X     X
10  X XXX XXX XXX XXXXX
11  X X         X     X
12  X X X X XXX XXXXX X
13  X X+X X+X    ZX   X
14  XXXXXXXXXXXXXXXXXXX

*/

  Terminal t{CreateTestTerminal1()};
  //Walk to enemy
  t.PressKey(Key::right);
  t.PressKey(Key::right);
  t.PressKey(Key::down);
  t.PressKey(Key::down);
  t.PressKey(Key::left);
  t.PressKey(Key::left);
  const auto before = to_str(t);
  t.RespondToCurrentSquare();
  const auto after = to_str(t);
  BOOST_CHECK_NE(before, after);
}
