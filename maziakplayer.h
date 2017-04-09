#ifndef MAZIAKPLAYER_H
#define MAZIAKPLAYER_H

#include <iosfwd>
#include <set>
#include "maziakcoordinat.h"
#include "maziakkey.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "maziakgamestate.h"

namespace ribi {
namespace maziak {

class Maze;

class Player
{
public:
  Player(const Coordinat c = {});

  GameState AnimateFighting() noexcept;

  auto GetCoordinat() const noexcept { return m_coordinat; }
  auto GetDirection() const noexcept { return m_direction; }
  auto GetMove() const noexcept { return m_move_now; }
  auto GetFightingFrame() const noexcept { return m_fighting_frame; }

  auto HasSword() const noexcept { return m_has_sword; }

  void PressKeys(const std::set<Key>& keys, const Maze& m, const bool do_show_solution);

  void SetCoordinat(const Coordinat c) noexcept { m_coordinat = c; }
  void SetHasSword(const bool b) noexcept { m_has_sword = b; }
  void SetFightingFrame(const int i) noexcept { m_fighting_frame = i; }

  ///The player stops moving and starts a waiting stance
  void Stop() noexcept { m_move_now = PlayerMove::none; }

private:
  Coordinat m_coordinat;
  PlayerDirection m_direction;
  int m_fighting_frame;
  bool m_has_sword;
  PlayerMove m_move_now;

  void MoveDown(const Maze& m, const bool do_show_solution);
  void MoveLeft(const Maze& m, const bool do_show_solution);
  void MoveRight(const Maze& m, const bool do_show_solution);
  void MoveUp(const Maze& m, const bool do_show_solution);
  void PressKey(const Key key, const Maze& m, const bool do_show_solution);

  friend std::ostream& operator<<(std::ostream& os, const Player& p) noexcept;
};

int get_col(const Player& p) noexcept;
int get_row(const Player& p) noexcept;
int get_x(const Player& p) noexcept;
int get_y(const Player& p) noexcept;

std::ostream& operator<<(std::ostream& os, const Player& p) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKPLAYER_H
