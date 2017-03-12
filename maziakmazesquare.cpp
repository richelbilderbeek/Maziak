#include "maziakmazesquare.h"

#include <cassert>



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

