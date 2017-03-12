#ifndef MAZIAKGAMESTATE_H
#define MAZIAKGAMESTATE_H

#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class GameState
{
  playing,
  has_won,
  game_over
};

std::string to_str(const GameState g) noexcept;

std::ostream& operator<<(std::ostream& os, const GameState g) noexcept;

} //~namespace maziak
} //~namespace ribi


#endif // MAZIAKGAMESTATE_H
