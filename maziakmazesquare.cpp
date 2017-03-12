#include "maziakmazesquare.h"

#include <cassert>

char ribi::maziak::to_char(const MazeSquare s) noexcept
{
  switch (s)
  {
    case MazeSquare::msEmpty: return ' ';
    case MazeSquare::msWall: return 'X';
    case MazeSquare::msEnemy1: return 'Z';
    case MazeSquare::msEnemy2: return 'z';
    case MazeSquare::msPrisoner1: return ':';
    case MazeSquare::msPrisoner2: return ';';
    case MazeSquare::msSword: return '+';
    case MazeSquare::msExit: return '!';
    case MazeSquare::msStart: return '.';
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return ' ';
}


std::string ribi::maziak::to_str(const MazeSquare s) noexcept
{
  switch (s)
  {
    case MazeSquare::msEmpty: return "empty";
    case MazeSquare::msWall: return "wall";
    case MazeSquare::msEnemy1: return "enemy1";
    case MazeSquare::msEnemy2: return "enemy2";
    case MazeSquare::msPrisoner1: return "prisoner1";
    case MazeSquare::msPrisoner2: return "prisoner2";
    case MazeSquare::msSword: return "sword";
    case MazeSquare::msExit: return "exit";
    case MazeSquare::msStart: return "start";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const MazeSquare s) noexcept
{
  os << to_str(s);
  return os;
}
