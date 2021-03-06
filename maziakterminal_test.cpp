#include "maziakterminal.h"

#include "maziakgame.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::maziak;

BOOST_AUTO_TEST_CASE(maziak_SolutionMaze_size)
{
  const Terminal t{create_test_terminal1()};
  BOOST_CHECK(!to_str(t).empty());
}

BOOST_AUTO_TEST_CASE(terminal_TogglePrisoners_must_animate)
{
  #ifdef FIX_ISSUE_20
  Terminal t{create_test_terminal1()};
  const auto before = to_str(t);
  t.TogglePrisoners();
  const auto after = to_str(t);
  BOOST_CHECK_NE(before, after);
  t.TogglePrisoners();
  const auto before_again = to_str(t);
  BOOST_CHECK_NE(before_again, after);
  BOOST_CHECK_EQUAL(before_again, before);
  #endif // FIX_ISSUE_20
}

BOOST_AUTO_TEST_CASE(terminal_stepping_on_prisoner_must_reveal_solution)
{
  Terminal t{create_test_terminal1()};
  BOOST_CHECK(!t.GetDoShowSolution());
  teleport_to(t, MazeSquare::prisoner);
  BOOST_CHECK(!t.GetDoShowSolution());
  assert(t.GetPlayerSquare() == MazeSquare::prisoner);
  t.RespondToCurrentSquare();
  BOOST_CHECK(t.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(terminal_solution_must_reveal_temporarily)
{
  Terminal t{create_test_terminal1()};
  teleport_to(t, MazeSquare::prisoner);
  t.RespondToCurrentSquare();
  assert(t.GetDoShowSolution());
  for (int i=0; i!=100; ++i)
  {
    t.Tick();
  }
  assert(!t.GetDoShowSolution());
}

BOOST_AUTO_TEST_CASE(terminal_fight_must_have_an_animation)
{
  Terminal t{create_test_terminal1()};
  teleport_to(t, MazeSquare::enemy);
  for (int i=0; i!=7; ++i)
  {
    const auto before = to_str(t);
    t.RespondToCurrentSquare();
    const auto after = to_str(t);
    BOOST_CHECK_NE(before, after);
  }
}

BOOST_AUTO_TEST_CASE(terminal_game_will_continue_after_fight_with_sword)
{
  Terminal t{create_test_terminal1()};
  BOOST_CHECK_EQUAL(t.GetGame().GetState(), GameState::playing);
  teleport_to(t, MazeSquare::enemy);
  BOOST_CHECK_EQUAL(t.GetGame().GetState(), GameState::playing);
  for (int i=0; i!=20; ++i)
  {
    t.RespondToCurrentSquare(); //Fight
  }
  BOOST_CHECK_EQUAL(t.GetGame().GetState(), GameState::playing);
}

BOOST_AUTO_TEST_CASE(terminal_game_will_end_after_fight_without_sword)
{
  Terminal t{create_test_terminal1()};
  //First enemy
  teleport_to(t, MazeSquare::enemy);
  for (int i=0; i!=20; ++i)
  {
    t.RespondToCurrentSquare(); //Fight
  }
  //Second enemy
  teleport_to(t, MazeSquare::enemy);
  BOOST_CHECK_EQUAL(t.GetGame().GetState(), GameState::playing);
  for (int i=0; i!=20; ++i)
  {
    t.RespondToCurrentSquare(); //Fight
  }
  BOOST_CHECK_EQUAL(t.GetGame().GetState(), GameState::game_over);
}
