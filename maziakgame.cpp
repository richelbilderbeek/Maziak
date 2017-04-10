#include "maziakgame.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/range/algorithm/remove.hpp>
#include "maziakkey.h"
#include "maziakmaze.h"
#include "maziakintmaze.h"
#include "maziakdistancesmaze.h"
#include "maziakplayer.h"
#include "maziaksolutionmaze.h"

ribi::maziak::Game::Game(
  const Maze& maze)
  :
    m_distances(maze, FindExit(maze)),
    m_do_show_solution{false},
    m_maze{maze},
    m_player{},
    m_rng_engine{42},
    m_solution{},
    m_state{GameState::playing}
{
  {
    const Coordinat start = FindStart(m_maze);
    m_player = Player(start);
  }
  m_solution = CreateNewSolution();
}

void ribi::maziak::Game::AnimateEnemiesAndPrisoners(
  const int view_width,
  const int view_height
) noexcept
{
  m_maze.AnimateEnemiesAndPrisoners(
    get_x(GetPlayer()),
    get_y(GetPlayer()),
    view_width,
    view_height,
    m_rng_engine
  );
}

void ribi::maziak::Game::AnimateFighting() noexcept
{
  assert(m_state != GameState::game_over);
  assert(m_state != GameState::has_won);
  m_state = m_player.AnimateFighting();
}

bool ribi::maziak::Game::CanGet(const Coordinat c) const noexcept
{
  return GetMaze().CanGet(c);
}

ribi::maziak::Game ribi::maziak::CreateTestGame1()
{
  return Game{CreateTestMaze1()};
}

ribi::maziak::SolutionMaze ribi::maziak::Game::CreateNewSolution() noexcept
{
  return SolutionMaze(m_distances, GetPlayer().GetCoordinat());
}

ribi::maziak::Coordinat ribi::maziak::FindFirst(const Game& m, const MazeSquare s)
{
  return FindFirst(m.GetMaze(), s);
}

int ribi::maziak::get_n_cols(const Game& g) noexcept
{
  return get_n_cols(g.GetMaze());
}

int ribi::maziak::get_n_rows(const Game& g) noexcept
{
  return get_n_rows(g.GetMaze());
}

ribi::maziak::Coordinat ribi::maziak::get_player_coordinat(const Game& g)
{
  return g.GetPlayer().GetCoordinat();
}

int ribi::maziak::get_player_x(const Game& g)
{
  return get_x(g.GetPlayer());
}

int ribi::maziak::get_player_y(const Game& g)
{
  return get_y(g.GetPlayer());
}

ribi::maziak::Sprite ribi::maziak::GetSpriteFloor(
  const Maze& maze,
  const Coordinat c,
  const bool do_show_solution,
  const SolutionMaze& solution
)
{
  assert(do_show_solution == false || get_n_rows(solution) == get_n_rows(maze));
  assert(do_show_solution == false || get_n_cols(solution) == get_n_cols(maze));

  //Outside of the maze are only walls
  if (!maze.CanGet(c))
  {
    return Sprite::wall;
  }
  assert(maze.CanGet(c));
  const MazeSquare s{maze.Get(c)};
  //Show golden road
  if (do_show_solution)
  {
    assert(get_n_rows(solution) == get_n_rows(maze));
    assert(get_n_cols(solution) == get_n_cols(maze));
    assert(solution.CanGet(c));
    if (solution.Get(c) == 1
      && ( s == MazeSquare::empty
        || s == MazeSquare::enemy
        || s == MazeSquare::start)
      )
    {
      return Sprite::path;
    }
  }
  //Show normal road
  return Sprite::empty;
}

ribi::maziak::Sprite ribi::maziak::GetSpriteAboveFloor(
  const Coordinat c,
  const Maze& maze,
  const int enemy_frame,
  const int prisoner_frame
)
{
  if (!maze.CanGet(c)) { return Sprite::wall; }
  //What else here?
  switch(maze.Get(c))
  {
    case MazeSquare::start:
    case MazeSquare::empty: return Sprite::empty;
    case MazeSquare::wall: return Sprite::wall;
    case MazeSquare::enemy:
      return enemy_frame % 2 == 0 ? Sprite::enemy1 : Sprite::enemy2;
    case MazeSquare::prisoner:
      return prisoner_frame % 2 == 0 ? Sprite::prisoner1 : Sprite::prisoner2;
    case MazeSquare::sword: return Sprite::sword;
    case MazeSquare::exit: return Sprite::exit;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::empty;
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpriteFloor(
  const Coordinat c) const
{
  return ::ribi::maziak::GetSpriteFloor(
    m_maze,
    c,
    m_do_show_solution,
    m_solution);
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpriteAboveFloor(
  const Coordinat c,
  const int enemy_frame,
  const int prisoner_frame
) const
{
  return ribi::maziak::GetSpriteAboveFloor(
    c,
    m_maze,
    enemy_frame,
    prisoner_frame
  );
}

ribi::maziak::Sprite ribi::maziak::Game::GetSpritePlayer() const
{
  return ::ribi::maziak::GetSpritePlayer(GetPlayer());
}

ribi::maziak::Sprite ribi::maziak::GetSpritePlayer(
  const Player& p
)
{
  const PlayerDirection direction = p.GetDirection();
  const PlayerMove move = p.GetMove();
  const bool has_sword = p.HasSword();
  const int fighting_frame = p.GetFightingFrame();

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
  return Sprite::empty;
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
  return Sprite::empty;
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
  return Sprite::empty;
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
  return Sprite::empty;
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
  return Sprite::empty;
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
    case  0: break;
    case 13: break;
    default: break;
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return Sprite::empty;
}

std::vector<ribi::maziak::Sprite>
ribi::maziak::Game::GetSprites(
  const Coordinat c,
  const int enemy_frame,
  const int prisoner_frame
) const
{
  std::vector<Sprite> v;
  //Out of screen
  if (!CanGet(c)) { return { Sprite::wall }; }
  //Player is always on top
  if (get_player_coordinat(*this) == c) { return { GetSpritePlayer() }; }
  v.push_back(this->GetSpriteFloor(c));
  v.push_back(this->GetSpriteAboveFloor(c, enemy_frame, prisoner_frame));
  if (v.size() >= 2 && v[0] == Sprite::empty) v.erase(std::begin(v));
  if (v.size() >= 2 && v[0] == Sprite::path && v[1] == Sprite::empty) v.erase(std::begin(v) + 1);
  return v;
}


void ribi::maziak::Game::PressKeys(const std::set<Key>& keys)
{
  m_player.PressKeys(keys, m_maze, m_do_show_solution);
}

void ribi::maziak::Game::RespondToCurrentSquare()
{
  if (m_state == GameState::game_over) return;
  if (m_state == GameState::has_won) return;

  if (m_player.IsFighting())
  {
    AnimateFighting();
    assert(m_state == GameState::playing || m_state == GameState::game_over);
    return;
  }

  assert(m_state == GameState::playing);

  const auto c = GetPlayer().GetCoordinat();
  assert(m_maze.CanGet(c));
  switch (m_maze.Get(c)) //Common encounters first
  {
    case MazeSquare::empty:
      break;
    case MazeSquare::prisoner:
      m_maze.Set(c, MazeSquare::empty);
      SetDoShowSolution(true);
      break;
    case MazeSquare::sword:
      m_maze.Set(c, MazeSquare::empty);
      m_player.SetHasSword(true);
      break;
    case MazeSquare::enemy:
      m_player.StartFighting();
      m_maze.Set(c, MazeSquare::empty); //Remove the enemy
      break;
    case MazeSquare::start:
      break;
    case MazeSquare::exit:
    {
      m_state = GameState::has_won;
      break;
    }
    case MazeSquare::wall:
      assert(!"Should not get here"); //!OCLINT accepted idiom
      break;
  }
}

void ribi::maziak::Game::SetDoShowSolution(const bool do_show) noexcept
{
  m_do_show_solution = do_show;
  if (m_do_show_solution)
  {
    m_solution = CreateNewSolution();
  }
}

void ribi::maziak::Game::SetPlayerPosition(const Coordinat p)
{
  m_player.SetCoordinat(p);
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

void ribi::maziak::teleport_to(Game& g, const MazeSquare s)
{
  const auto target_coordinat = FindFirst(g.GetMaze(), s);
  g.SetPlayerPosition(target_coordinat);
}


std::string ribi::maziak::to_str(const Game& d) noexcept
{
  std::stringstream s;
  s << d;
  return s.str();
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const Game& d) noexcept
{
  os
    << "distances: " << d.m_distances << '\n'
    << "do_show_solution: " << d.m_do_show_solution << '\n'
    << "maze: " << d.m_maze << '\n'
    << "solution: " << d.m_solution << '\n'
    << "state: " << d.m_state << '\n'
    << "player: " << d.m_player << '\n'
  ;
  return os;
}
