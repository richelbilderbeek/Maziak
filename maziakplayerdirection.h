#ifndef MAZIAKPLAYERDIRECTION_H
#define MAZIAKPLAYERDIRECTION_H

#include <array>
#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class PlayerDirection
{
  pdLeft,
  pdRight,
  pdUp,
  pdDown
};

constexpr std::array<PlayerDirection, 4> get_all_player_directions()
{
  return
  {
    PlayerDirection::pdLeft,
    PlayerDirection::pdRight,
    PlayerDirection::pdUp,
    PlayerDirection::pdDown
  };
}

std::string to_str(const PlayerDirection d) noexcept;

std::ostream& operator<<(std::ostream& os, const PlayerDirection d) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKPLAYERDIRECTION_H
