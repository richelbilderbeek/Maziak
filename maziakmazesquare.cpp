#include "maziakmazesquare.h"

#include <cassert>
#include <iostream>

std::string ribi::maziak::to_str(const MazeSquare s) noexcept
{
  switch (s)
  {
    case MazeSquare::empty: return "empty";
    case MazeSquare::wall: return "wall";
    case MazeSquare::enemy: return "enemy";
    case MazeSquare::prisoner: return "prisoner";
    case MazeSquare::sword: return "sword";
    case MazeSquare::exit: return "exit";
    case MazeSquare::start: return "start";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const MazeSquare s) noexcept
{
  os << to_char(s);
  return os;
}
