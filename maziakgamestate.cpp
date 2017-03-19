#include "maziakgamestate.h"

#include <cassert>
#include <iostream>


std::string ribi::maziak::to_str(const GameState g) noexcept
{
  switch (g)
  {
    case GameState::playing: return "playing";
    case GameState::has_won: return "has_won";
    case GameState::game_over: return "game_over";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const GameState g) noexcept
{
  os << to_str(g);
  return os;
}
