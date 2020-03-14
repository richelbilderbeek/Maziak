#ifndef MAZIAKPLAYERMOVE_H
#define MAZIAKPLAYERMOVE_H

#include <array>
#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class PlayerMove {
  none,
  left1,
  left2,
  right1,
  right2,
  up1,
  up2,
  down1,
  down2
};

constexpr std::array<PlayerMove, 9> get_all_player_moves()
{
  return
  {
    PlayerMove::none,
    PlayerMove::left1,
    PlayerMove::left2,
    PlayerMove::right1,
    PlayerMove::right2,
    PlayerMove::up1,
    PlayerMove::up2,
    PlayerMove::down1,
    PlayerMove::down2
  };
}

std::string to_str(const PlayerMove m) noexcept;
std::ostream& operator<<(std::ostream& os, const PlayerMove m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKPLAYERMOVE_H
