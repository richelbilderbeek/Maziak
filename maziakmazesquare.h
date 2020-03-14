#ifndef MAZIAKMAZESQUARE_H
#define MAZIAKMAZESQUARE_H

#include <array>
#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class MazeSquare
{
  empty,
  wall,
  enemy,
  prisoner,
  sword,
  exit,
  start //Initial starting position
};

constexpr std::array<MazeSquare, 7> get_all_maze_squares()
{
  return
  {
    MazeSquare::empty,
    MazeSquare::wall,
    MazeSquare::enemy,
    MazeSquare::prisoner,
    MazeSquare::sword,
    MazeSquare::exit,
    MazeSquare::start
  };
}

///ASCII art
constexpr char to_char(const MazeSquare s) noexcept
{
  switch (s)
  {
    case MazeSquare::empty: return ' ';
    case MazeSquare::wall: return 'X';
    case MazeSquare::enemy: return 'Z';
    case MazeSquare::prisoner: return ':';
    case MazeSquare::sword: return '+';
    case MazeSquare::exit: return '!';
    case MazeSquare::start: return '.';
  }
  return '?';
}

std::string to_str(const MazeSquare s) noexcept;

std::ostream& operator<<(std::ostream& os, const MazeSquare s) noexcept;


} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMAZESQUARE_H
