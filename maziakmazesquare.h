#ifndef MAZIAKMAZESQUARE_H
#define MAZIAKMAZESQUARE_H

#include <iosfwd>
#include <initializer_list>
#include <string>

namespace ribi {
namespace maziak {

enum class MazeSquare
{
  msEmpty,
  msWall,
  msEnemy1,
  msEnemy2,
  msPrisoner,
  msSword,
  msExit,
  msStart //Initial starting position
};

constexpr std::initializer_list<MazeSquare> get_all_maze_squares()
{
  return
  {
    MazeSquare::msEmpty,
    MazeSquare::msWall,
    MazeSquare::msEnemy1,
    MazeSquare::msEnemy2,
    MazeSquare::msPrisoner,
    MazeSquare::msSword,
    MazeSquare::msExit,
    MazeSquare::msStart
  };
}

///ASCII art
char to_char(const MazeSquare s) noexcept;

std::string to_str(const MazeSquare s) noexcept;

std::ostream& operator<<(std::ostream& os, const MazeSquare s) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMAZESQUARE_H
