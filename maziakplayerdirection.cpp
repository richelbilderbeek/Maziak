#include "maziakplayerdirection.h"

#include <cassert>
#include <iostream>

std::string ribi::maziak::to_str(const PlayerDirection d) noexcept
{
  switch (d)
  {
    case PlayerDirection::pdDown: return "down";
    case PlayerDirection::pdLeft: return "left";
    case PlayerDirection::pdRight: return "right";
    case PlayerDirection::pdUp: return "up";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::ostream& ribi::maziak::operator<<(
  std::ostream& os, const PlayerDirection d) noexcept
{
  os << to_str(d);
  return os;
}

