#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "maziakgame.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/range/algorithm/remove.hpp>
#include "maziakkey.h"
#include "maziakmaze.h"
#include "maziakdisplay.h"
#include "maziakintmaze.h"
#include "maziakdistancesmaze.h"
#include "maziakreceiver.h"
#include "maziaksolutionmaze.h"
#include "maziaksprites.h"


#pragma GCC diagnostic pop

ribi::maziak::Game::Game(
  const Maze& maze)
  : m_direction(PlayerDirection::pdDown),
    m_distances(maze, FindExit(maze)),
    m_do_show_solution{false},
    m_fighting_frame(0),
    m_has_sword(true),
    m_maze{maze},
    m_move_now(PlayerMove::none),
    m_rng_engine{42},
    m_solution{},
    m_state{GameState::playing},
    m_x(-1),
    m_y(-1)
{
  {
    const std::pair<int,int> start = FindStart(m_maze);
    m_x = start.first;
    m_y = start.second;
  }
  m_solution = CreateNewSolution();
}

void ribi::maziak::Game::AnimateEnemiesAndPrisoners(
  const int view_width,
  const int view_height
) noexcept
{
  m_maze.AnimateEnemiesAndPrisoners(
    m_x,
    m_y,
    view_width,
    view_height,
    m_rng_engine
  );
}

void ribi::maziak::Game::AnimateFighting() noexcept
{
  if (m_fighting_frame > 0)
  {
    ++m_fighting_frame;
    if (m_fighting_frame == 13)
    {
      if (!m_has_sword)
      {
        m_state = GameState::game_over;
        return;
      }
      m_fighting_frame = 0;
      m_has_sword = false;
    }
  }
}

bool ribi::maziak::Game::CanGet(const int x, const int y) const noexcept
{
  return GetMaze().CanGet(x, y);
}

ribi::maziak::Game ribi::maziak::CreateTestGame1()
{
  return Game{CreateTestMaze1()};
}

ribi::maziak::SolutionMaze ribi::maziak::Game::CreateNewSolution() noexcept
{
  SolutionMaze solution(m_distances,m_x,m_y);
  return solution;
}

ribi::maziak::Sprite ribi::maziak::GetSpriteFloor(
  const Maze& maze,
  const int x,
  const int y,
  const bool do_show_solution,
  const SolutionMaze& solution
)
{
  assert(do_show_solution == false || get_n_rows(solution) == get_n_rows(maze));

  //Outside of the maze are only walls
  if (!maze.CanGet(x,y))
  {
    return Sprite::wall;
  }
  const MazeSquare s{maze.Get(x,y)};
  //Show golden road
  if (do_show_solution
    && solution.Get(x,y) == 1
    && ( s == MazeSquare::msEmpty
      || s == MazeSquare::msEnemy
      || s == MazeSquare::msStart)
    )
  {
    return Sprite::path;
  }
  //Show normal road
  return Sprite::empty;
}

ribi::maziak::Sprite ribi::maziak::GetSpriteAboveFloor(
  const int x,
  const int y,
  const Maze& maze,
  const int enemy_frame,
  const int prisoner_frame
)
{
  if (!maze.CanGet(x,y)) { return Sprite::wall; }
  //What else here?
  switch(maze.Get(x,y))
  {
    case MazeSquare::msStart   :
    case MazeSquare::msEmpty   : return Sprite::transparent;
    case MazeSquare::msWall    : return Sprite::wall;
    case MazeSquare::msEnemy   : return enemy_frame % 2 == 0 ? Sprite::enemy1 : Sprite::enemy2;
    case MazeSquare::msPrisoner: return prisoner_frame % 2 == 0 ? Sprite::prisoner1 : Sprite::prisoner2;
    case MazeSquare::msSword   : return Sprite::sword;
    case MazeSquare::msExit    : return Sprite::exit;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpriteFloor(
  const int x, const int y) const
{
  return ::ribi::maziak::GetSpriteFloor(
    m_maze,
    x,
    y,
    m_do_show_solution,
    m_solution);
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpriteAboveFloor(
  const int x,
  const int y,
  const int enemy_frame,
  const int prisoner_frame
) const
{
  return ribi::maziak::GetSpriteAboveFloor(
    x,
    y,
    m_maze,
    enemy_frame,
    prisoner_frame
  );
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpritePlayer() const
{
  return ::ribi::maziak::GetSpritePlayer(
    m_direction,
    m_move_now,
    m_has_sword,
    m_fighting_frame
  );
}

ribi::maziak::Sprite ribi::maziak::GetSpritePlayer(
  const PlayerDirection direction,
  const PlayerMove move,
  const bool has_sword,
  const int fighting_frame
)
{
  if (fighting_frame != 0) return GetSpritePlayerFighting(fighting_frame, has_sword);
  assert(fighting_frame == 0);
  switch (direction)
  {
    case PlayerDirection::pdUp: return GetSpritePlayerUp(move, has_sword);
    case PlayerDirection::pdRight: return GetSpritePlayerRight(move, has_sword);
    case PlayerDirection::pdDown: return GetSpritePlayerDown(move, has_sword);
    case PlayerDirection::pdLeft: return GetSpritePlayerLeft(move, has_sword);
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}

ribi::maziak::Sprite ribi::maziak::GetSpritePlayerDown(
  const PlayerMove move,
  const bool has_sword
)
{
  switch (move)
  {
    case PlayerMove::none:  return has_sword
      ? Sprite::player_look_down_sword : Sprite::player_look_down;
    case PlayerMove::down1: return has_sword
      ? Sprite::player_walk_down_sword1 : Sprite::player_walk_down1;
    case PlayerMove::down2: return has_sword
      ? Sprite::player_walk_down_sword2 : Sprite::player_walk_down2;
    default:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      break;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}

ribi::maziak::Sprite ribi::maziak::GetSpritePlayerLeft(
  const PlayerMove move,
  const bool has_sword
)
{
  switch (move)
  {
    case PlayerMove::none:  return has_sword
      ? Sprite::player_look_left_sword : Sprite::player_look_left;
    case PlayerMove::left1: return has_sword
      ? Sprite::player_walk_left_sword1 : Sprite::player_walk_left1;
    case PlayerMove::left2: return has_sword
      ? Sprite::player_walk_left_sword2 : Sprite::player_walk_left2;
    default:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      break;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}


ribi::maziak::Sprite ribi::maziak::GetSpritePlayerRight(
  const PlayerMove move,
  const bool has_sword
)
{
  switch (move)
  {
    case PlayerMove::none:   return has_sword
      ? Sprite::player_look_right_sword : Sprite::player_look_right;
    case PlayerMove::right1: return has_sword
      ? Sprite::player_walk_right_sword1 : Sprite::player_walk_right1;
    case PlayerMove::right2: return has_sword
      ? Sprite::player_walk_right_sword2 : Sprite::player_walk_right2;
    default:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      break;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}


ribi::maziak::Sprite ribi::maziak::GetSpritePlayerUp(
  const PlayerMove move,
  const bool has_sword
)
{
  switch (move)
  {
    case PlayerMove::none: return has_sword
      ? Sprite::player_look_up_sword : Sprite::player_look_up;
    case PlayerMove::up1:  return has_sword
      ? Sprite::player_walk_up_sword1 : Sprite::player_walk_up1;
    case PlayerMove::up2:  return has_sword
      ? Sprite::player_walk_up_sword2 : Sprite::player_walk_up2;
    default:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      break;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}


ribi::maziak::Sprite ribi::maziak::GetSpritePlayerFighting( //!OCLINT cannot lower cyclomatic complexity without impairing readability
  const int fighting_frame,
  const bool has_sword
)
{
  switch (fighting_frame)
  {
    case  1: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  2: return Sprite::fight2;
    case  3: return Sprite::fight3;
    case  4: return Sprite::fight4;
    case  5: return has_sword ? Sprite::fight_sword1 : Sprite::fight_no_sword1;
    case  6: return Sprite::fight2;
    case  7: return Sprite::fight3;
    case  8: return Sprite::fight4;
    case  9: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 10: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
    case 11: return has_sword ? Sprite::fight_won1 : Sprite::fight_lost1;
    case 12: return has_sword ? Sprite::fight_won2 : Sprite::fight_lost2;
    case  0:
    case 13:
    default: assert(!"Should not get here"); //!OCLINT accepted idiom
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::transparent;
}

std::vector<ribi::maziak::Sprite>
ribi::maziak::Game::GetSprites(
  const int x,
  const int y,
  const int enemy_frame,
  const int prisoner_frame
) const
{
  std::vector<Sprite> v;
  if (!CanGet(x, y)) { return { Sprite::wall }; }
  v.push_back(this->GetSpriteFloor(x,y));
  v.push_back(this->GetSpriteAboveFloor(x, y, enemy_frame, prisoner_frame));
  const auto new_end = boost::range::remove(v, Sprite::transparent);
  v.erase(new_end, std::end(v));
  if (v.size() >= 2 && v[0] == Sprite::empty) v.erase(std::begin(v));
  return v;
}

void ribi::maziak::Game::PressKey(const Key key)
{
  switch (key)
  {
    case Key::left : PressKeyLeft(); break;
    case Key::right: PressKeyRight(); break;
    case Key::up   : PressKeyUp(); break;
    case Key::down : PressKeyDown(); break;
    case Key::quit :
    case Key::none : m_move_now = PlayerMove::none; break;
  }
}

void ribi::maziak::Game::PressKeyDown()
{
  m_direction = PlayerDirection::pdDown;
  if (!m_maze.CanMoveTo(m_x,m_y+1,m_has_sword,m_do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::down1
    ? PlayerMove::down2 : PlayerMove::down1);
  ++m_y;
}

void ribi::maziak::Game::PressKeyLeft()
{
  m_direction = PlayerDirection::pdLeft;
  if (!m_maze.CanMoveTo(m_x-1,m_y,m_has_sword,m_do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::left1
    ? PlayerMove::left2 : PlayerMove::left1);
  --m_x;
}

void ribi::maziak::Game::PressKeyRight()
{
  m_direction = PlayerDirection::pdRight;
  if (!m_maze.CanMoveTo(m_x+1,m_y,m_has_sword,m_do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::right1
    ? PlayerMove::right2 : PlayerMove::right1);
  ++m_x;
}

void ribi::maziak::Game::PressKeyUp()
{
  m_direction = PlayerDirection::pdUp;
  if (!m_maze.CanMoveTo(m_x,m_y-1,m_has_sword,m_do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::up1
    ? PlayerMove::up2 : PlayerMove::up1);
  --m_y;
}

void ribi::maziak::Game::PressKeys(const std::set<Key>& keys)
{
  if (m_fighting_frame > 0) return;
  if (keys.empty()) { m_move_now = PlayerMove::none; return; }

  for(const Key key: keys)
  {
    PressKey(key);
  }
}

void ribi::maziak::Game::RespondToCurrentSquare()
{
  assert(m_maze.CanGet(m_x,m_y));
  switch (m_maze.Get(m_x,m_y))
  {
    case MazeSquare::msStart:
    case MazeSquare::msEmpty:
      return;
    case MazeSquare::msWall:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      return;
    case MazeSquare::msEnemy:
      m_fighting_frame = 1;
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      return;
    case MazeSquare::msPrisoner:
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      SetDoShowSolution(true);
      return;
    case MazeSquare::msSword:
      m_maze.Set(m_x,m_y,MazeSquare::msEmpty);
      m_has_sword = true;
      return;
    case MazeSquare::msExit:
    {
      m_state = GameState::has_won;
      return;
    }
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
}

void ribi::maziak::Game::SetDoShowSolution(const bool do_show) noexcept
{
  m_do_show_solution = do_show;
  if (m_do_show_solution)
  {
    m_solution = CreateNewSolution();
  }
}


/*
void ribi::maziak::Game::Tick()
{
  if (this->GetState() == GameState::game_over) return;
  if (this->GetState() == GameState::has_won) return;

  //HACK: let the player move less often than the framerate
  {
    static boost::timer t;
    if (t.elapsed() > 0.05)
    {
      const auto keys = m_display->RequestKeys();
      PressKeys(keys);
      t.restart();
    }
  }

  if (m_display) m_do_show_solution = m_display->GetDoShowSolution();

  RespondToCurrentSquare();

  if (m_display)
  {
    const int view_width  = m_display->GetViewWidth(); //Was 20
    const int view_height = m_display->GetViewHeight(); //Was 20
    if (m_display->MustAnimateEnemiesAndPrisoners())
    {
      AnimateEnemiesAndPrisoners(view_width,view_height);
    }
  }
  if(m_fighting_frame > 0)
  {
    AnimateFighting();
  }
}
*/


std::string ribi::maziak::to_str(const Game& d) noexcept
{
  std::stringstream s;
  s << d;
  return s.str();
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const Game& d) noexcept
{
  os
    << "direction: " << d.m_direction << '\n'
    << "distances: " << d.m_distances << '\n'
    << "do_show_solution: " << d.m_do_show_solution << '\n'
    << "fighting_frame: " << d.m_fighting_frame << '\n'
    << "has_sword: " << d.m_has_sword << '\n'
    << "maze: " << d.m_maze << '\n'
    << "move_now: " << d.m_move_now << '\n'
    << "solution: " << d.m_solution << '\n'
    << "state: " << d.m_state << '\n'
    << "x: " << d.m_x << '\n'
    << "y: " << d.m_y << '\n'
  ;
  return os;
}
