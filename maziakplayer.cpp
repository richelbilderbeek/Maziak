#include "maziakplayer.h"

#include <iostream>
#include "maziakmaze.h"

ribi::maziak::Player::Player(const Coordinat c)
  : m_coordinat{c},
    m_direction{PlayerDirection::pdDown},
    m_fighting_frame{0},
    m_has_sword{true},
    m_move_now(PlayerMove::none)
{

}

ribi::maziak::GameState ribi::maziak::Player::AnimateFighting() noexcept
{
  if (m_fighting_frame > 0)
  {
    ++m_fighting_frame;
    if (m_fighting_frame == 13)
    {
      if (!HasSword())
      {
        return GameState::game_over;
      }
      m_fighting_frame = 0;
      SetHasSword(false);
    }
  }
  return GameState::playing;
}

int ribi::maziak::get_col(const Player& p) noexcept { return get_col(p.GetCoordinat()); }
int ribi::maziak::get_row(const Player& p) noexcept { return get_row(p.GetCoordinat()); }
int ribi::maziak::get_x(const Player& p) noexcept { return get_x(p.GetCoordinat()); }
int ribi::maziak::get_y(const Player& p) noexcept { return get_y(p.GetCoordinat()); }

void ribi::maziak::Player::MoveDown(
  const Maze& m,
  const bool do_show_solution
)
{
  const Coordinat target = get_below(m_coordinat);
  m_direction = PlayerDirection::pdDown;
  if (!m.CanMoveTo(target,m_has_sword,do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::down1
    ? PlayerMove::down2 : PlayerMove::down1);

  m_coordinat = target;
}

void ribi::maziak::Player::MoveLeft(
  const Maze& m,
  const bool do_show_solution
)
{
  const Coordinat target = get_left(m_coordinat);
  m_direction = PlayerDirection::pdLeft;
  if (!m.CanMoveTo(target, m_has_sword,do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::left1
    ? PlayerMove::left2 : PlayerMove::left1);

  m_coordinat = target;
}

void ribi::maziak::Player::MoveRight(
  const Maze& m,
  const bool do_show_solution
)
{
  const Coordinat target = get_right(m_coordinat);
  m_direction = PlayerDirection::pdRight;
  if (!m.CanMoveTo(target, m_has_sword,do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::right1
    ? PlayerMove::right2 : PlayerMove::right1);

  m_coordinat = target;
}

void ribi::maziak::Player::MoveUp(
  const Maze& m,
  const bool do_show_solution
)
{
  const Coordinat target = get_above(m_coordinat);
  m_direction = PlayerDirection::pdUp;
  if (!m.CanMoveTo(target, m_has_sword,do_show_solution))
  {
    m_move_now = PlayerMove::none;
    return;
  }
  m_move_now = (m_move_now == PlayerMove::up1
    ? PlayerMove::up2 : PlayerMove::up1);

  m_coordinat = target;
}

void ribi::maziak::Player::PressKey(const Key key, const Maze& m, const bool do_show_solution)
{
  switch (key)
  {
    case Key::left : MoveLeft(m, do_show_solution); break;
    case Key::right: MoveRight(m, do_show_solution); break;
    case Key::up   : MoveUp(m, do_show_solution); break;
    case Key::down : MoveDown(m, do_show_solution); break;
    case Key::quit :
    case Key::none : Stop(); break;
  }
}

void ribi::maziak::Player::PressKeys(
  const std::set<Key>& keys,
  const Maze& m,
  const bool do_show_solution)
{
  //Do not respond when fighting
  if (m_fighting_frame > 0) return;

  //Take waiting stance when no input
  if (keys.empty()) { Stop(); return; }

  for(const Key key: keys)
  {
    PressKey(key, m, do_show_solution);
  }
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const Player& p) noexcept
{
  os
    << "coordinat: " << p.m_coordinat << '\n'
    << "direction: " << p.m_direction << '\n'
    << "fighting_frame: " << p.m_fighting_frame << '\n'
    << "has_sword: " << p.m_has_sword << '\n'
    << "move_now: " << p.m_move_now << '\n'
  ;
  return os;
}
