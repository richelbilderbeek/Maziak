#ifndef MAZIAKPLAYERDIRECTION_H
#define MAZIAKPLAYERDIRECTION_H

#include <iosfwd>
#include <string>
#include <initializer_list>

namespace ribi {
namespace maziak {

enum class PlayerDirection
{
  pdLeft,
  pdRight,
  pdUp,
  pdDown
};

constexpr std::initializer_list<PlayerDirection> get_all_player_directions()
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
