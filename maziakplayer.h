#ifndef MAZIAKPLAYER_H
#define MAZIAKPLAYER_H

#include <iosfwd>
#include "maziakcoordinat.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"

namespace ribi {
namespace maziak {

class Maze;

class Player
{
public:
  Player(const Coordinat c = {});

  auto GetCoordinat() const noexcept { return m_coordinat; }
  auto GetDirection() const noexcept { return m_direction; }
  auto GetMove() const noexcept { return m_move_now; }

  auto HasSword() const noexcept { return m_has_sword; }

  void MoveDown(const Maze& m, const bool do_show_solution);
  void MoveLeft(const Maze& m, const bool do_show_solution);
  void MoveRight(const Maze& m, const bool do_show_solution);
  void MoveUp(const Maze& m, const bool do_show_solution);

  void SetCoordinat(const Coordinat c) noexcept { m_coordinat = c; }
  void SetHasSword(const bool b) noexcept { m_has_sword = b; }

  ///The player stops moving and starts a waiting stance
  void Stop() noexcept { m_move_now = PlayerMove::none; }

private:
  Coordinat m_coordinat;
  PlayerDirection m_direction;
  bool m_has_sword;
  PlayerMove m_move_now;

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
