#ifndef MAZIAKMAZESQUARE_H
#define MAZIAKMAZESQUARE_H

#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class MazeSquare
{
  msEmpty,
  msWall,
  msEnemy1,
  msEnemy2,
  msPrisoner1,
  msPrisoner2,
  msSword,
  msExit,
  msStart //Initial starting position
};

///ASCII art
char to_char(const MazeSquare s) noexcept;

std::string to_str(const MazeSquare s) noexcept;

std::ostream& operator<<(std::ostream& os, const MazeSquare s) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMAZESQUARE_H
